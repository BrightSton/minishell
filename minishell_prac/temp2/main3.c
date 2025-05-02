/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 05:05:31 by djang             #+#    #+#             */
/*   Updated: 2025/05/01 05:05:32 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>

#define MAX_TOKENS 128
#define MAX_TOKEN_LEN 1024

int g_exit_code = 0;
volatile sig_atomic_t g_heredoc_interrupted = 0;

typedef struct s_env {
    char *key;
    char *value;
    struct s_env *next;
} t_env;

typedef struct s_token {
    char *str;
} t_token;

typedef struct s_redir {
    char *type;
    char *file;
    struct s_redir *next;
    int heredoc_fd;
} t_redir;

typedef struct s_cmd {
    char **argv;
    int argc;
    t_redir *redir;
    struct s_cmd *next;
} t_cmd;

// ========== 시그널 핸들러 ==========
void sigint_handler(int signo) {
    (void)signo;
    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}
void heredoc_sigint_handler(int signo) {
    (void)signo;
    g_heredoc_interrupted = 1;
    write(1, "\n", 1);
    exit(130);
}
void sigquit_handler(int signo) {
    (void)signo;
}

// ========== 환경변수 ==========
t_env *init_env(char **envp) {
    t_env *head = NULL, *tail = NULL;
    for (int i = 0; envp[i]; i++) {
        char *eq = strchr(envp[i], '=');
        if (!eq) continue;
        t_env *node = malloc(sizeof(t_env));
        node->key = strndup(envp[i], eq - envp[i]);
        node->value = strdup(eq + 1);
        node->next = NULL;
        if (!head) head = node;
        else tail->next = node;
        tail = node;
    }
    return head;
}
void free_env(t_env *env) {
    while (env) {
        t_env *next = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = next;
    }
}
char *get_env_value(t_env *env, const char *key) {
    for (; env; env = env->next)
        if (!strcmp(env->key, key))
            return env->value;
    return NULL;
}
void ms_env(t_env *env_list) {
    for (t_env *cur = env_list; cur; cur = cur->next)
        printf("%s=%s\n", cur->key, cur->value);
}
int is_valid_key(const char *key) {
    if (!key || !isalpha(key[0])) return 0;
    for (int i = 1; key[i]; i++)
        if (!isalnum(key[i]) && key[i] != '_') return 0;
    return 1;
}
void ms_export(t_env **env_list, const char *assignment) {
    char *eq = strchr(assignment, '=');
    if (!eq) {
        fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", assignment);
        g_exit_code = 1;
        return;
    }
    char *key = strndup(assignment, eq - assignment);
    if (!is_valid_key(key)) {
        fprintf(stderr, "minishell: export: `%s': not a valid identifier\n", key);
        free(key);
        g_exit_code = 1;
        return;
    }
    char *value = strdup(eq + 1);
    for (t_env *cur = *env_list; cur; cur = cur->next) {
        if (strcmp(cur->key, key) == 0) {
            free(cur->value);
            cur->value = value;
            free(key);
            g_exit_code = 0;
            return;
        }
    }
    t_env *node = malloc(sizeof(t_env));
    node->key = key;
    node->value = value;
    node->next = *env_list;
    *env_list = node;
    g_exit_code = 0;
}
void ms_unset(t_env **env_list, const char *key) {
    t_env *prev = NULL, *cur = *env_list;
    while (cur) {
        if (strcmp(cur->key, key) == 0) {
            if (prev) prev->next = cur->next;
            else *env_list = cur->next;
            free(cur->key);
            free(cur->value);
            free(cur);
            g_exit_code = 0;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    g_exit_code = 0;
}
char **env_list_to_envp(t_env *env) {
    int count = 0;
    t_env *tmp = env;
    while (tmp) {
        count++;
        tmp = tmp->next;
    }
    char **envp = malloc(sizeof(char *) * (count + 1));
    tmp = env;
    for (int i = 0; i < count; i++) {
        int len = strlen(tmp->key) + strlen(tmp->value) + 2;
        envp[i] = malloc(len);
        snprintf(envp[i], len, "%s=%s", tmp->key, tmp->value);
        tmp = tmp->next;
    }
    envp[count] = NULL;
    return envp;
}
void free_envp(char **envp) {
    for (int i = 0; envp[i]; i++)
        free(envp[i]);
    free(envp);
}

// ========== $VAR 확장 ==========
char *expand_vars(const char *src, t_env *env) {
    char result[4096] = {0};
    int ri = 0;
    for (int i = 0; src[i]; ) {
        if (src[i] == '$' && (isalpha(src[i+1]) || src[i+1] == '_')) {
            int j = i+1;
            while (isalnum(src[j]) || src[j] == '_') j++;
            char key[256] = {0};
            strncpy(key, src+i+1, j-i-1);
            char *val = get_env_value(env, key);
            if (val) {
                int k = 0;
                while (val[k]) result[ri++] = val[k++];
            }
            i = j;
        } else {
            result[ri++] = src[i++];
        }
    }
    result[ri] = 0;
    return strdup(result);
}
void expand_argv_vars(t_cmd *cmd, t_env *env_list) {
    for (int i = 0; i < cmd->argc; i++) {
        char *expanded = expand_vars(cmd->argv[i], env_list);
        free(cmd->argv[i]);
        cmd->argv[i] = expanded;
    }
}

// ========== 파싱/구문 오류 체크 ==========
void add_token(t_token *tokens, int *count, char *buf, int len) {
    if (len <= 0) return;
    buf[len] = '\0';
    tokens[*count].str = strdup(buf);
    (*count)++;
}
int parse_line(const char *line, t_token *tokens) {
    int i = 0, count = 0;
    char buf[MAX_TOKEN_LEN];
    int buf_idx = 0;
    int in_single = 0, in_double = 0;

    while (line[i]) {
        if (!in_single && !in_double && isspace(line[i])) {
            add_token(tokens, &count, buf, buf_idx);
            buf_idx = 0;
            while (isspace(line[i])) i++;
        }
        else if (!in_single && !in_double && (line[i] == '|' || line[i] == '<' || line[i] == '>')) {
            add_token(tokens, &count, buf, buf_idx);
            buf_idx = 0;
            if ((line[i] == '>' && line[i+1] == '>') || (line[i] == '<' && line[i+1] == '<')) {
                buf[0] = line[i];
                buf[1] = line[i+1];
                add_token(tokens, &count, buf, 2);
                i += 2;
            } else {
                buf[0] = line[i];
                add_token(tokens, &count, buf, 1);
                i++;
            }
        }
        else if (line[i] == '\'' && !in_double) {
            in_single = !in_single;
            i++;
        }
        else if (line[i] == '"' && !in_single) {
            in_double = !in_double;
            i++;
        }
        else {
            buf[buf_idx++] = line[i++];
        }
    }
    add_token(tokens, &count, buf, buf_idx);
    return count;
}
int is_redir(const char *token) {
    return (!strcmp(token, ">") || !strcmp(token, "<") ||
            !strcmp(token, ">>") || !strcmp(token, "<<"));
}
int is_pipe(const char *token) {
    return (!strcmp(token, "|"));
}
int check_syntax(t_token *tokens, int token_count) {
    if (token_count == 0) return 0;
    if (!strcmp(tokens[0].str, "|") || !strcmp(tokens[token_count-1].str, "|")) {
        fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
        g_exit_code = 2;
        return 2;
    }
    for (int i = 0; i < token_count; i++) {
        if (is_pipe(tokens[i].str) && (i+1 < token_count && is_pipe(tokens[i+1].str))) {
            fprintf(stderr, "minishell: syntax error near unexpected token `|'\n");
            g_exit_code = 2;
            return 2;
        }
        if (is_redir(tokens[i].str) && (i+1 >= token_count || is_redir(tokens[i+1].str) || is_pipe(tokens[i+1].str))) {
            fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n", tokens[i].str);
            g_exit_code = 2;
            return 2;
        }
    }
    return 0;
}

// ========== 명령어 구조체화 ==========
t_redir *new_redir(char *type, char *file) {
    t_redir *redir = malloc(sizeof(t_redir));
    redir->type = strdup(type);
    redir->file = strdup(file);
    redir->next = NULL;
    redir->heredoc_fd = -1;
    return redir;
}
void add_redir(t_redir **head, t_redir *new) {
    if (*head == NULL) {
        *head = new;
        return;
    }
    t_redir *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
t_cmd *new_cmd(void) {
    t_cmd *cmd = malloc(sizeof(t_cmd));
    cmd->argv = malloc(sizeof(char *) * MAX_TOKENS);
    cmd->argc = 0;
    cmd->redir = NULL;
    cmd->next = NULL;
    return cmd;
}
void add_cmd(t_cmd **head, t_cmd *new) {
    if (*head == NULL) {
        *head = new;
        return;
    }
    t_cmd *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new;
}
t_cmd *create_cmd_list(t_token *tokens, int token_count) {
    t_cmd *cmd_list = NULL;
    t_cmd *current_cmd = NULL;
    int i = 0;
    while (i < token_count) {
        if (cmd_list == NULL || (i > 0 && is_pipe(tokens[i - 1].str))) {
            current_cmd = new_cmd();
            add_cmd(&cmd_list, current_cmd);
        }
        if (is_redir(tokens[i].str)) {
            if (i + 1 < token_count) {
                t_redir *redir = new_redir(tokens[i].str, tokens[i + 1].str);
                add_redir(&current_cmd->redir, redir);
                i += 2;
            } else {
                printf("Error: missing file for redirection\n");
                i++;
            }
        }
        else if (is_pipe(tokens[i].str)) {
            i++;
        }
        else {
            current_cmd->argv[current_cmd->argc++] = strdup(tokens[i].str);
            current_cmd->argv[current_cmd->argc] = NULL;
            i++;
        }
    }
    return cmd_list;
}
void free_cmd_list(t_cmd *cmd_list) {
    while (cmd_list) {
        t_cmd *next_cmd = cmd_list->next;
        for (int i = 0; i < cmd_list->argc; i++)
            free(cmd_list->argv[i]);
        free(cmd_list->argv);
        t_redir *redir = cmd_list->redir;
        while (redir) {
            t_redir *next_redir = redir->next;
            free(redir->type);
            free(redir->file);
            if (redir->heredoc_fd != -1) close(redir->heredoc_fd);
            free(redir);
            redir = next_redir;
        }
        free(cmd_list);
        cmd_list = next_cmd;
    }
}

// ========== 빌트인/외부 명령어 실행 ==========
int is_builtin(const char *cmd) {
    return (!strcmp(cmd, "echo") ||
            !strcmp(cmd, "cd") ||
            !strcmp(cmd, "pwd") ||
            !strcmp(cmd, "exit") ||
            !strcmp(cmd, "export") ||
            !strcmp(cmd, "unset") ||
            !strcmp(cmd, "env"));
}
int exec_builtin(t_cmd *cmd, t_env **env_list) {
    if (!strcmp(cmd->argv[0], "echo")) {
        int n_flag = 0, i = 1;
        if (cmd->argc > 1 && strcmp(cmd->argv[1], "-n") == 0) {
            n_flag = 1;
            i = 2;
        }
        for (; i < cmd->argc; i++) {
            printf("%s", cmd->argv[i]);
            if (i < cmd->argc - 1) printf(" ");
        }
        if (!n_flag) printf("\n");
        g_exit_code = 0;
        return 0;
    }
    else if (!strcmp(cmd->argv[0], "pwd")) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)))
            printf("%s\n", cwd);
        else
            perror("pwd");
        g_exit_code = 0;
        return 0;
    }
    else if (!strcmp(cmd->argv[0], "cd")) {
        const char *path = (cmd->argc > 1) ? cmd->argv[1] : get_env_value(*env_list, "HOME");
        if (!path)
            path = ".";
        if (chdir(path) != 0) {
            perror("cd");
            g_exit_code = 1;
            return 1;
        }
        g_exit_code = 0;
        return 0;
    }
    else if (!strcmp(cmd->argv[0], "exit")) {
        int status = 0;
        if (cmd->argc > 1)
            status = atoi(cmd->argv[1]);
        printf("exit\n");
        exit(status);
    }
    else if (!strcmp(cmd->argv[0], "env")) {
        ms_env(*env_list);
        g_exit_code = 0;
        return 0;
    }
    else if (!strcmp(cmd->argv[0], "export")) {
        if (cmd->argc > 1) {
            for (int i = 1; i < cmd->argc; i++)
                ms_export(env_list, cmd->argv[i]);
        }
        g_exit_code = 0;
        return 0;
    }
    else if (!strcmp(cmd->argv[0], "unset")) {
        if (cmd->argc > 1) {
            for (int i = 1; i < cmd->argc; i++)
                ms_unset(env_list, cmd->argv[i]);
        }
        g_exit_code = 0;
        return 0;
    }
    return -1;
}
char *find_path(char *cmd, t_env *env_list) {
    if (strchr(cmd, '/'))
        return strdup(cmd);
    char *path_env = get_env_value(env_list, "PATH");
    if (!path_env) return NULL;
    char *paths = strdup(path_env);
    char *saveptr = NULL;
    char *dir = strtok_r(paths, ":", &saveptr);
    while (dir) {
        char full[1024];
        snprintf(full, sizeof(full), "%s/%s", dir, cmd);
        if (access(full, X_OK) == 0) {
            free(paths);
            return strdup(full);
        }
        dir = strtok_r(NULL, ":", &saveptr);
    }
    free(paths);
    return NULL;
}
void exec_external(t_cmd *cmd, t_env *env_list) {
    char **envp = env_list_to_envp(env_list);
    char *path = find_path(cmd->argv[0], env_list);
    if (!path) {
        fprintf(stderr, "minishell: command not found: %s\n", cmd->argv[0]);
        free_envp(envp);
        exit(127);
    }
    execve(path, cmd->argv, envp);
    fprintf(stderr, "minishell: %s: %s\n", cmd->argv[0], strerror(errno));
    free(path);
    free_envp(envp);
    exit(126);
}

// ========== heredoc 및 파이프/리다이렉션 실행 ==========
int heredoc_to_pipe_child(const char *limiter, int write_fd) {
    signal(SIGINT, heredoc_sigint_handler);
    while (1) {
        char *line = readline("> ");
        if (!line) break;
        if (strcmp(line, limiter) == 0) {
            free(line);
            break;
        }
        write(write_fd, line, strlen(line));
        write(write_fd, "\n", 1);
        free(line);
    }
    close(write_fd);
    exit(0);
}
int heredoc_to_pipe(const char *limiter) {
    int pipefd[2];
    if (pipe(pipefd) < 0) {
        perror("pipe");
        return -1;
    }
    g_heredoc_interrupted = 0;
    pid_t pid = fork();
    if (pid == 0) {
        close(pipefd[0]);
        heredoc_to_pipe_child(limiter, pipefd[1]);
    }
    close(pipefd[1]);
    int status;
    waitpid(pid, &status, 0);
    if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT) {
        g_heredoc_interrupted = 1;
        close(pipefd[0]);
        return -1;
    }
    return pipefd[0];
}
void handle_heredoc_redirs(t_cmd *cmd) {
    for (t_redir *r = cmd->redir; r; r = r->next) {
        if (!strcmp(r->type, "<<")) {
            r->heredoc_fd = heredoc_to_pipe(r->file);
            if (g_heredoc_interrupted) break;
        }
    }
}
void execute_cmd_list_with_pipe(t_cmd *cmd_list, t_env *env_list) {
    for (t_cmd *cmd = cmd_list; cmd; cmd = cmd->next) {
        handle_heredoc_redirs(cmd);
        if (g_heredoc_interrupted) {
            fprintf(stderr, "[DEBUG] heredoc interrupted, skipping execution\n");
            return;
        }
    }

    int prev_pipe_fd[2] = {-1, -1};
    t_cmd *cmd = cmd_list;
    int proc_count = 0;

    while (cmd) {
        expand_argv_vars(cmd, env_list);
        int pipe_fd[2] = {-1, -1};
        int is_last = (cmd->next == NULL);

        if (!is_last) {
            if (pipe(pipe_fd) < 0) {
                perror("pipe");
                exit(1);
            }
        }

        if (is_builtin(cmd->argv[0]) &&
            (!strcmp(cmd->argv[0], "cd") ||
             !strcmp(cmd->argv[0], "export") ||
             !strcmp(cmd->argv[0], "unset") ||
             !strcmp(cmd->argv[0], "env"))) {
            fprintf(stderr, "[DEBUG] parent executes builtin: %s\n", cmd->argv[0]);
            exec_builtin(cmd, &env_list);
            cmd = cmd->next;
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            for (t_redir *r = cmd->redir; r; r = r->next) {
                int fd = -1;
                if (!strcmp(r->type, "<"))
                    fd = open(r->file, O_RDONLY);
                else if (!strcmp(r->type, ">"))
                    fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                else if (!strcmp(r->type, ">>"))
                    fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                else if (!strcmp(r->type, "<<") && r->heredoc_fd != -1)
                    fd = r->heredoc_fd;
                if (fd < 0) {
                    fprintf(stderr, "minishell: %s: %s\n", r->file, strerror(errno));
                    exit(1);
                }
                if (!strcmp(r->type, "<") || !strcmp(r->type, "<<"))
                    dup2(fd, STDIN_FILENO);
                else
                    dup2(fd, STDOUT_FILENO);
                if (fd != r->heredoc_fd) close(fd);
            }
            if (prev_pipe_fd[0] != -1) {
                dup2(prev_pipe_fd[0], STDIN_FILENO);
                close(prev_pipe_fd[0]);
            }
            if (!is_last) {
                close(pipe_fd[0]);
                dup2(pipe_fd[1], STDOUT_FILENO);
                close(pipe_fd[1]);
            }
            if (is_builtin(cmd->argv[0])) {
                exec_builtin(cmd, &env_list);
                exit(g_exit_code);
            } else {
                exec_external(cmd, env_list);
            }
        } else if (pid < 0) {
            perror("fork");
            exit(1);
        }
        fprintf(stderr, "[DEBUG] forked child %d (cmd: %s)\n", pid, cmd->argv[0]);
        proc_count++;
        if (prev_pipe_fd[0] != -1) close(prev_pipe_fd[0]);
        if (prev_pipe_fd[1] != -1) close(prev_pipe_fd[1]);
        prev_pipe_fd[0] = pipe_fd[0];
        prev_pipe_fd[1] = pipe_fd[1];
        if (!is_last) close(pipe_fd[1]);
        cmd = cmd->next;
    }
    int waited = 0;
    int status;
    while (wait(&status) > 0) {
        waited++;
        fprintf(stderr, "[DEBUG] child exited (waited: %d)\n", waited);
    }
    if (proc_count != waited)
        fprintf(stderr, "[DEBUG] WARNING: not all children exited! (proc_count=%d, waited=%d)\n", proc_count, waited);
}

// ========== 메인 ==========
int main(int argc, char **argv, char **envp) {
    signal(SIGINT, sigint_handler);
    signal(SIGQUIT, sigquit_handler);

    t_env *env_list = init_env(envp);
    char *line;

    while (1) {
        line = readline("minishell$ ");
        if (!line) {
            printf("exit\n");
            break;
        }
        if (*line)
            add_history(line);

        t_token tokens[MAX_TOKENS] = {0};
        int token_count = parse_line(line, tokens);

        int syntax_status = check_syntax(tokens, token_count);
        if (syntax_status) {
            for (int i = 0; i < token_count; i++) free(tokens[i].str);
            free(line);
            continue;
        }

        t_cmd *cmd_list = create_cmd_list(tokens, token_count);

        if (cmd_list && cmd_list->argc > 0 && !strcmp(cmd_list->argv[0], "exit")) {
            expand_argv_vars(cmd_list, env_list);
            exec_builtin(cmd_list, &env_list);
        }
        else if (cmd_list && cmd_list->next == NULL && is_builtin(cmd_list->argv[0]) &&
            (!strcmp(cmd_list->argv[0], "cd") ||
             !strcmp(cmd_list->argv[0], "export") ||
             !strcmp(cmd_list->argv[0], "unset") ||
             !strcmp(cmd_list->argv[0], "env"))) {
            expand_argv_vars(cmd_list, env_list);
            exec_builtin(cmd_list, &env_list);
        } else {
            execute_cmd_list_with_pipe(cmd_list, env_list);
        }

        for (int i = 0; i < token_count; i++)
            free(tokens[i].str);
        free_cmd_list(cmd_list);
        free(line);
    }
    free_env(env_list);
    return 0;
}

