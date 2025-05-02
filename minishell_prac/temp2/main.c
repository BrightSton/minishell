/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:11:42 by djang             #+#    #+#             */
/*   Updated: 2025/04/29 22:11:44 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//#define MAX_TOKENS 100

//// 공백 기준으로 나누는 함수
//char **split_by_space(char *line)
//{
//    char **tokens = malloc(sizeof(char *) * (MAX_TOKENS + 1));
//    int i = 0;
//    char *token = strtok(line, " ");
//    while (token && i < MAX_TOKENS)
//    {
//        tokens[i++] = strdup(token);
//        token = strtok(NULL, " ");
//    }
//    tokens[i] = NULL;
//    return tokens;
//}

//int main(void)
//{
//    char *line;
//    while ((line = readline("minishell$ ")) != NULL)
//    {
//        if (*line)
//            add_history(line);

//        // 파싱
//        char **tokens = split_by_space(line);

//        // 토큰 출력
//        printf("토큰화 결과:\n");
//        for (int i = 0; tokens[i]; i++)
//            printf("[%s]\n", tokens[i]);

//        // 메모리 해제
//        for (int i = 0; tokens[i]; i++)
//            free(tokens[i]);
//        free(tokens);
//        free(line);
//    }
//    return 0;
//}


//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//#define MAX_TOKENS 128

//// 토큰을 저장할 구조체
//typedef struct s_token
//{
//    char *str;
//} t_token;

//// 토큰 추가 함수
//void add_token(t_token *tokens, int *count, const char *start, int len)
//{
//    if (len <= 0) return;
//    tokens[*count].str = strndup(start, len);
//    (*count)++;
//}

//// 파싱 함수
//int parse_line(const char *line, t_token *tokens)
//{
//    int i = 0, start = 0, count = 0;
//    int in_single = 0, in_double = 0;
//    while (line[i])
//    {
//        // 따옴표 상태 토글
//        if (line[i] == '\'' && !in_double)
//            in_single = !in_single, i++;
//        else if (line[i] == '"' && !in_single)
//            in_double = !in_double, i++;
//        // 따옴표 밖에서 공백
//        else if (!in_single && !in_double && isspace(line[i]))
//        {
//            add_token(tokens, &count, line + start, i - start);
//            while (isspace(line[i])) i++;
//            start = i;
//        }
//        // 따옴표 밖에서 |, <, > (리다이렉션 2글자도 처리)
//        else if (!in_single && !in_double &&
//                (line[i] == '|' || line[i] == '<' || line[i] == '>'))
//        {
//            add_token(tokens, &count, line + start, i - start);
//            if ((line[i] == '>' && line[i+1] == '>') ||
//                (line[i] == '<' && line[i+1] == '<'))
//            {
//                add_token(tokens, &count, line + i, 2);
//                i += 2;
//            }
//            else
//            {
//                add_token(tokens, &count, line + i, 1);
//                i++;
//            }
//            start = i;
//        }
//        else
//            i++;
//    }
//    // 마지막 토큰 추가
//    add_token(tokens, &count, line + start, i - start);
//    return count;
//}

//int main(void)
//{
//    char *line;
//    while ((line = readline("minishell$ ")) != NULL)
//    {
//        if (*line)
//            add_history(line);

//        t_token tokens[MAX_TOKENS] = {0};
//        int count = parse_line(line, tokens);

//        printf("토큰화 결과:\n");
//        for (int i = 0; i < count; i++)
//            printf("[%s]\n", tokens[i].str);

//        for (int i = 0; i < count; i++)
//            free(tokens[i].str);
//        free(line);
//    }
//    return 0;
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//#define MAX_TOKENS 128
//#define MAX_TOKEN_LEN 1024

//typedef struct s_token
//{
//    char *str;
//} t_token;

//void add_token(t_token *tokens, int *count, char *buf, int len)
//{
//    if (len <= 0) return;
//    buf[len] = '\0';
//    tokens[*count].str = strdup(buf);
//    (*count)++;
//}

//int parse_line(const char *line, t_token *tokens)
//{
//    int i = 0, count = 0;
//    char buf[MAX_TOKEN_LEN];
//    int buf_idx = 0;
//    int in_single = 0, in_double = 0;

//    while (line[i])
//    {
//        if (!in_single && !in_double && isspace(line[i]))
//        {
//            add_token(tokens, &count, buf, buf_idx);
//            buf_idx = 0;
//            while (isspace(line[i])) i++;
//        }
//        else if (!in_single && !in_double && (line[i] == '|' || line[i] == '<' || line[i] == '>'))
//        {
//            add_token(tokens, &count, buf, buf_idx);
//            buf_idx = 0;
//            if ((line[i] == '>' && line[i+1] == '>') || (line[i] == '<' && line[i+1] == '<'))
//            {
//                buf[0] = line[i];
//                buf[1] = line[i+1];
//                add_token(tokens, &count, buf, 2);
//                i += 2;
//            }
//            else
//            {
//                buf[0] = line[i];
//                add_token(tokens, &count, buf, 1);
//                i++;
//            }
//        }
//        else if (line[i] == '\'' && !in_double)
//        {
//            in_single = !in_single;
//            i++; // 따옴표는 토큰에 넣지 않음
//        }
//        else if (line[i] == '"' && !in_single)
//        {
//            in_double = !in_double;
//            i++; // 따옴표는 토큰에 넣지 않음
//        }
//        else
//        {
//            buf[buf_idx++] = line[i++];
//        }
//    }
//    add_token(tokens, &count, buf, buf_idx);
//    return count;
//}

//int main(void)
//{
//    char *line;
//    while ((line = readline("minishell$ ")) != NULL)
//    {
//        if (*line)
//            add_history(line);

//        t_token tokens[MAX_TOKENS] = {0};
//        int count = parse_line(line, tokens);

//        printf("토큰화 결과:\n");
//        for (int i = 0; i < count; i++)
//            printf("[%s]\n", tokens[i].str);

//        for (int i = 0; i < count; i++)
//            free(tokens[i].str);
//        free(line);
//    }
//    return 0;
//}



//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//#define MAX_TOKENS 128
//#define MAX_TOKEN_LEN 1024

//// 토큰 구조체
//typedef struct s_token {
//    char *str;
//} t_token;

//// 리다이렉션 구조체
//typedef struct s_redir {
//    char *type;           // ">", "<", ">>", "<<"
//    char *file;           // 리다이렉션 파일명
//    struct s_redir *next; // 다음 리다이렉션
//} t_redir;

//// 명령어 구조체
//typedef struct s_cmd {
//    char **argv;          // 명령어와 인자들
//    int argc;             // 인자 개수
//    t_redir *redir;       // 리다이렉션 정보
//    struct s_cmd *next;   // 파이프로 연결된 다음 명령어
//} t_cmd;

//// 토큰 추가 함수
//void add_token(t_token *tokens, int *count, char *buf, int len)
//{
//    if (len <= 0) return;
//    buf[len] = '\0';
//    tokens[*count].str = strdup(buf);
//    (*count)++;
//}

//// 토큰화 함수
//int parse_line(const char *line, t_token *tokens)
//{
//    int i = 0, count = 0;
//    char buf[MAX_TOKEN_LEN];
//    int buf_idx = 0;
//    int in_single = 0, in_double = 0;

//    while (line[i])
//    {
//        if (!in_single && !in_double && isspace(line[i]))
//        {
//            add_token(tokens, &count, buf, buf_idx);
//            buf_idx = 0;
//            while (isspace(line[i])) i++;
//        }
//        else if (!in_single && !in_double && (line[i] == '|' || line[i] == '<' || line[i] == '>'))
//        {
//            add_token(tokens, &count, buf, buf_idx);
//            buf_idx = 0;
//            if ((line[i] == '>' && line[i+1] == '>') || (line[i] == '<' && line[i+1] == '<'))
//            {
//                buf[0] = line[i];
//                buf[1] = line[i+1];
//                add_token(tokens, &count, buf, 2);
//                i += 2;
//            }
//            else
//            {
//                buf[0] = line[i];
//                add_token(tokens, &count, buf, 1);
//                i++;
//            }
//        }
//        else if (line[i] == '\'' && !in_double)
//        {
//            in_single = !in_single;
//            i++;
//        }
//        else if (line[i] == '"' && !in_single)
//        {
//            in_double = !in_double;
//            i++;
//        }
//        else
//        {
//            buf[buf_idx++] = line[i++];
//        }
//    }
//    add_token(tokens, &count, buf, buf_idx);
//    return count;
//}

//// 새로운 리다이렉션 노드 생성
//t_redir *new_redir(char *type, char *file)
//{
//    t_redir *redir = malloc(sizeof(t_redir));
//    redir->type = strdup(type);
//    redir->file = strdup(file);
//    redir->next = NULL;
//    return redir;
//}

//// 리다이렉션 노드 추가
//void add_redir(t_redir **head, t_redir *new)
//{
//    if (*head == NULL)
//    {
//        *head = new;
//        return;
//    }
//    t_redir *tmp = *head;
//    while (tmp->next)
//        tmp = tmp->next;
//    tmp->next = new;
//}

//// 새로운 명령어 노드 생성
//t_cmd *new_cmd(void)
//{
//    t_cmd *cmd = malloc(sizeof(t_cmd));
//    cmd->argv = malloc(sizeof(char *) * MAX_TOKENS);
//    cmd->argc = 0;
//    cmd->redir = NULL;
//    cmd->next = NULL;
//    return cmd;
//}

//// 명령어 노드 추가
//void add_cmd(t_cmd **head, t_cmd *new)
//{
//    if (*head == NULL)
//    {
//        *head = new;
//        return;
//    }
//    t_cmd *tmp = *head;
//    while (tmp->next)
//        tmp = tmp->next;
//    tmp->next = new;
//}

//// 토큰이 리다이렉션인지 확인
//int is_redir(char *token)
//{
//    return (!strcmp(token, ">") || !strcmp(token, "<") || 
//            !strcmp(token, ">>") || !strcmp(token, "<<"));
//}

//// 토큰이 파이프인지 확인
//int is_pipe(char *token)
//{
//    return (!strcmp(token, "|"));
//}

//// 토큰 배열을 명령어 구조체로 변환
//t_cmd *create_cmd_list(t_token *tokens, int token_count)
//{
//    t_cmd *cmd_list = NULL;
//    t_cmd *current_cmd = NULL;
//    int i = 0;

//    while (i < token_count)
//    {
//        // 새 명령어 시작 (첫 토큰이거나 파이프 다음)
//        if (cmd_list == NULL || is_pipe(tokens[i - 1].str))
//        {
//            current_cmd = new_cmd();
//            add_cmd(&cmd_list, current_cmd);
//        }

//        // 리다이렉션 처리
//        if (is_redir(tokens[i].str))
//        {
//            if (i + 1 < token_count) // 파일명이 있는지 확인
//            {
//                t_redir *redir = new_redir(tokens[i].str, tokens[i + 1].str);
//                add_redir(&current_cmd->redir, redir);
//                i += 2; // 리다이렉션 기호와 파일명 건너뛰기
//            }
//            else
//            {
//                // 에러: 리다이렉션 후 파일명 없음
//                printf("Error: missing file for redirection\n");
//                i++;
//            }
//        }
//        // 파이프 처리
//        else if (is_pipe(tokens[i].str))
//        {
//            i++; // 파이프 건너뛰기
//        }
//        // 일반 인자 처리
//        else
//        {
//            current_cmd->argv[current_cmd->argc++] = strdup(tokens[i].str);
//            current_cmd->argv[current_cmd->argc] = NULL; // NULL로 배열 종료
//            i++;
//        }
//    }

//    return cmd_list;
//}

//// 명령어 구조체 출력 (디버깅용)
//void print_cmd_list(t_cmd *cmd_list)
//{
//    int cmd_num = 1;
//    while (cmd_list)
//    {
//        printf("Command %d:\n", cmd_num++);
        
//        printf("  Arguments: ");
//        for (int i = 0; i < cmd_list->argc; i++)
//            printf("[%s] ", cmd_list->argv[i]);
//        printf("\n");
        
//        t_redir *redir = cmd_list->redir;
//        if (redir)
//            printf("  Redirections:\n");
//        while (redir)
//        {
//            printf("    %s %s\n", redir->type, redir->file);
//            redir = redir->next;
//        }
        
//        cmd_list = cmd_list->next;
//        if (cmd_list)
//            printf("  | (piped to)\n");
//    }
//}

//// 명령어 구조체 메모리 해제
//void free_cmd_list(t_cmd *cmd_list)
//{
//    while (cmd_list)
//    {
//        t_cmd *next_cmd = cmd_list->next;
        
//        // argv 해제
//        for (int i = 0; i < cmd_list->argc; i++)
//            free(cmd_list->argv[i]);
//        free(cmd_list->argv);
        
//        // 리다이렉션 해제
//        t_redir *redir = cmd_list->redir;
//        while (redir)
//        {
//            t_redir *next_redir = redir->next;
//            free(redir->type);
//            free(redir->file);
//            free(redir);
//            redir = next_redir;
//        }
        
//        free(cmd_list);
//        cmd_list = next_cmd;
//    }
//}

//int main(void)
//{
//    char *line;
//    while ((line = readline("minishell$ ")) != NULL)
//    {
//        if (*line)
//            add_history(line);

//        // 1. 토큰화
//        t_token tokens[MAX_TOKENS] = {0};
//        int token_count = parse_line(line, tokens);

//        printf("토큰화 결과:\n");
//        for (int i = 0; i < token_count; i++)
//            printf("[%s]\n", tokens[i].str);
        
//        // 2. 명령어 구조체 생성
//        t_cmd *cmd_list = create_cmd_list(tokens, token_count);
        
//        //t_cmd *cmd_list;
//        //cmd_list = create_cmd_list(tokens, token_count);
        
        
//        // 3. 명령어 구조체 출력
//        printf("\n명령어 구조:\n");
//        print_cmd_list(cmd_list);
        
//        // 4. 메모리 해제
//        for (int i = 0; i < token_count; i++)
//            free(tokens[i].str);
//        free_cmd_list(cmd_list);
//        free(line);
//    }
//    return 0;
//}


//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/wait.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//#define MAX_TOKENS 128
//#define MAX_TOKEN_LEN 1024

//typedef struct s_token {
//    char *str;
//} t_token;

//typedef struct s_redir {
//    char *type;           // ">", "<", ">>", "<<"
//    char *file;
//    struct s_redir *next;
//} t_redir;

//typedef struct s_cmd {
//    char **argv;
//    int argc;
//    t_redir *redir;
//    struct s_cmd *next;
//} t_cmd;

//// 토큰 추가
//void add_token(t_token *tokens, int *count, char *buf, int len) {
//    if (len <= 0) return;
//    buf[len] = '\0';
//    tokens[*count].str = strdup(buf);
//    (*count)++;
//}

//// 토큰화
//int parse_line(const char *line, t_token *tokens) {
//    int i = 0, count = 0;
//    char buf[MAX_TOKEN_LEN];
//    int buf_idx = 0;
//    int in_single = 0, in_double = 0;

//    while (line[i]) {
//        if (!in_single && !in_double && isspace(line[i])) {
//            add_token(tokens, &count, buf, buf_idx);
//            buf_idx = 0;
//            while (isspace(line[i])) i++;
//        }
//        else if (!in_single && !in_double && (line[i] == '|' || line[i] == '<' || line[i] == '>')) {
//            add_token(tokens, &count, buf, buf_idx);
//            buf_idx = 0;
//            if ((line[i] == '>' && line[i+1] == '>') || (line[i] == '<' && line[i+1] == '<')) {
//                buf[0] = line[i];
//                buf[1] = line[i+1];
//                add_token(tokens, &count, buf, 2);
//                i += 2;
//            } else {
//                buf[0] = line[i];
//                add_token(tokens, &count, buf, 1);
//                i++;
//            }
//        }
//        else if (line[i] == '\'' && !in_double) {
//            in_single = !in_single;
//            i++;
//        }
//        else if (line[i] == '"' && !in_single) {
//            in_double = !in_double;
//            i++;
//        }
//        else {
//            buf[buf_idx++] = line[i++];
//        }
//    }
//    add_token(tokens, &count, buf, buf_idx);
//    return count;
//}

//// 리다이렉션 구조체 생성/추가
//t_redir *new_redir(char *type, char *file) {
//    t_redir *redir = malloc(sizeof(t_redir));
//    redir->type = strdup(type);
//    redir->file = strdup(file);
//    redir->next = NULL;
//    return redir;
//}
//void add_redir(t_redir **head, t_redir *new) {
//    if (*head == NULL) {
//        *head = new;
//        return;
//    }
//    t_redir *tmp = *head;
//    while (tmp->next)
//        tmp = tmp->next;
//    tmp->next = new;
//}

//// 명령어 구조체 생성/추가
//t_cmd *new_cmd(void) {
//    t_cmd *cmd = malloc(sizeof(t_cmd));
//    cmd->argv = malloc(sizeof(char *) * MAX_TOKENS);
//    cmd->argc = 0;
//    cmd->redir = NULL;
//    cmd->next = NULL;
//    return cmd;
//}
//void add_cmd(t_cmd **head, t_cmd *new) {
//    if (*head == NULL) {
//        *head = new;
//        return;
//    }
//    t_cmd *tmp = *head;
//    while (tmp->next)
//        tmp = tmp->next;
//    tmp->next = new;
//}

//// 토큰 타입 판별
//int is_redir(char *token) {
//    return (!strcmp(token, ">") || !strcmp(token, "<") || 
//            !strcmp(token, ">>") || !strcmp(token, "<<"));
//}
//int is_pipe(char *token) {
//    return (!strcmp(token, "|"));
//}

//// 토큰 배열 → 명령어 구조체 리스트 변환
//t_cmd *create_cmd_list(t_token *tokens, int token_count) {
//    t_cmd *cmd_list = NULL;
//    t_cmd *current_cmd = NULL;
//    int i = 0;

//    while (i < token_count) {
//        if (cmd_list == NULL || (i > 0 && is_pipe(tokens[i - 1].str))) {
//            current_cmd = new_cmd();
//            add_cmd(&cmd_list, current_cmd);
//        }
//        if (is_redir(tokens[i].str)) {
//            if (i + 1 < token_count) {
//                t_redir *redir = new_redir(tokens[i].str, tokens[i + 1].str);
//                add_redir(&current_cmd->redir, redir);
//                i += 2;
//            } else {
//                printf("Error: missing file for redirection\n");
//                i++;
//            }
//        }
//        else if (is_pipe(tokens[i].str)) {
//            i++;
//        }
//        else {
//            current_cmd->argv[current_cmd->argc++] = strdup(tokens[i].str);
//            current_cmd->argv[current_cmd->argc] = NULL;
//            i++;
//        }
//    }
//    return cmd_list;
//}

//// 빌트인 명령어 판별
//int is_builtin(const char *cmd) {
//    return (!strcmp(cmd, "echo") ||
//            !strcmp(cmd, "cd") ||
//            !strcmp(cmd, "pwd") ||
//            !strcmp(cmd, "export") ||
//            !strcmp(cmd, "unset") ||
//            !strcmp(cmd, "env") ||
//            !strcmp(cmd, "exit"));
//}

//// 빌트인 명령어 실행 (echo만 예시)
//int exec_builtin(t_cmd *cmd) {
//    if (!strcmp(cmd->argv[0], "echo")) {
//        for (int i = 1; i < cmd->argc; i++) {
//            printf("%s", cmd->argv[i]);
//            if (i < cmd->argc - 1) printf(" ");
//        }
//        printf("\n");
//        return 0;
//    }
//    // 나머지 빌트인은 직접 추가
//    return -1;
//}

//// 외부 명령어 실행
//void exec_external(t_cmd *cmd, char **envp) {
//    pid_t pid = fork();
//    if (pid == 0) {
//        execvp(cmd->argv[0], cmd->argv);
//        perror("execvp");
//        exit(1);
//    } else if (pid > 0) {
//        int status;
//        waitpid(pid, &status, 0);
//    } else {
//        perror("fork");
//    }
//}

//// 명령어 리스트 실행
//void execute_cmd_list(t_cmd *cmd_list, char **envp) {
//    while (cmd_list) {
//        if (cmd_list->argc == 0) {
//            cmd_list = cmd_list->next;
//            continue;
//        }
//        if (is_builtin(cmd_list->argv[0])) {
//            exec_builtin(cmd_list);
//        } else {
//            exec_external(cmd_list, envp);
//        }
//        cmd_list = cmd_list->next;
//    }
//}

//// 메모리 해제
//void free_cmd_list(t_cmd *cmd_list) {
//    while (cmd_list) {
//        t_cmd *next_cmd = cmd_list->next;
//        for (int i = 0; i < cmd_list->argc; i++)
//            free(cmd_list->argv[i]);
//        free(cmd_list->argv);
//        t_redir *redir = cmd_list->redir;
//        while (redir) {
//            t_redir *next_redir = redir->next;
//            free(redir->type);
//            free(redir->file);
//            free(redir);
//            redir = next_redir;
//        }
//        free(cmd_list);
//        cmd_list = next_cmd;
//    }
//}

//int main(int argc, char **argv, char **envp) {
//    char *line;
//    while ((line = readline("minishell$ ")) != NULL) {
//        if (*line)
//            add_history(line);

//        t_token tokens[MAX_TOKENS] = {0};
//        int token_count = parse_line(line, tokens);

//        t_cmd *cmd_list = create_cmd_list(tokens, token_count);

//        execute_cmd_list(cmd_list, envp);

//        for (int i = 0; i < token_count; i++)
//            free(tokens[i].str);
//        free_cmd_list(cmd_list);
//        free(line);
//    }
//    return 0;
//}


//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/wait.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//#define MAX_TOKENS 128
//#define MAX_TOKEN_LEN 1024

//typedef struct s_env {
//    char *key;
//    char *value;
//    struct s_env *next;
//} t_env;

//typedef struct s_token {
//    char *str;
//} t_token;

//typedef struct s_cmd {
//    char **argv;
//    int argc;
//    struct s_cmd *next;
//} t_cmd;

//// 환경변수 리스트 초기화
//t_env *init_env(char **envp) {
//    t_env *head = NULL, *tail = NULL;
//    for (int i = 0; envp[i]; i++) {
//        char *eq = strchr(envp[i], '=');
//        if (!eq) continue;
//        t_env *node = malloc(sizeof(t_env));
//        node->key = strndup(envp[i], eq - envp[i]);
//        node->value = strdup(eq + 1);
//        node->next = NULL;
//        if (!head) head = node;
//        else tail->next = node;
//        tail = node;
//    }
//    return head;
//}

//// 환경변수 리스트 해제
//void free_env(t_env *env) {
//    while (env) {
//        t_env *next = env->next;
//        free(env->key);
//        free(env->value);
//        free(env);
//        env = next;
//    }
//}

//// 환경변수 값 얻기
//char *get_env_value(t_env *env, const char *key) {
//    for (; env; env = env->next)
//        if (!strcmp(env->key, key))
//            return env->value;
//    return NULL;
//}

//// env 빌트인
//void ms_env(t_env *env_list) {
//    for (t_env *cur = env_list; cur; cur = cur->next)
//        printf("%s=%s\n", cur->key, cur->value);
//}

//// export 빌트인
//void ms_export(t_env **env_list, const char *assignment) {
//    char *eq = strchr(assignment, '=');
//    if (!eq) {
//        fprintf(stderr, "export: invalid assignment: %s\n", assignment);
//        return;
//    }
//    char *key = strndup(assignment, eq - assignment);
//    char *value = strdup(eq + 1);

//    // 이미 있는 key면 value만 교체
//    for (t_env *cur = *env_list; cur; cur = cur->next) {
//        if (strcmp(cur->key, key) == 0) {
//            free(cur->value);
//            cur->value = value;
//            free(key);
//            return;
//        }
//    }
//    // 없으면 새 노드 추가
//    t_env *node = malloc(sizeof(t_env));
//    node->key = key;
//    node->value = value;
//    node->next = *env_list;
//    *env_list = node;
//}

//// unset 빌트인
//void ms_unset(t_env **env_list, const char *key) {
//    t_env *prev = NULL, *cur = *env_list;
//    while (cur) {
//        if (strcmp(cur->key, key) == 0) {
//            if (prev) prev->next = cur->next;
//            else *env_list = cur->next;
//            free(cur->key);
//            free(cur->value);
//            free(cur);
//            return;
//        }
//        prev = cur;
//        cur = cur->next;
//    }
//}

//// 토크나이저 (공백만 분리, 따옴표/특수문자 생략 버전)
//int parse_line(const char *line, t_token *tokens) {
//    int count = 0;
//    char *copy = strdup(line);
//    char *tok = strtok(copy, " \t\n");
//    while (tok && count < MAX_TOKENS) {
//        tokens[count].str = strdup(tok);
//        count++;
//        tok = strtok(NULL, " \t\n");
//    }
//    free(copy);
//    return count;
//}

//// 명령어 구조체 생성
//t_cmd *create_cmd(t_token *tokens, int token_count) {
//    t_cmd *cmd = malloc(sizeof(t_cmd));
//    cmd->argv = malloc(sizeof(char *) * (token_count + 1));
//    cmd->argc = 0;
//    for (int i = 0; i < token_count; i++) {
//        cmd->argv[cmd->argc++] = strdup(tokens[i].str);
//    }
//    cmd->argv[cmd->argc] = NULL;
//    cmd->next = NULL;
//    return cmd;
//}
//void free_cmd(t_cmd *cmd) {
//    for (int i = 0; i < cmd->argc; i++)
//        free(cmd->argv[i]);
//    free(cmd->argv);
//    free(cmd);
//}

//// 빌트인 판별
//int is_builtin(const char *cmd) {
//    return (!strcmp(cmd, "echo") ||
//            !strcmp(cmd, "cd") ||
//            !strcmp(cmd, "pwd") ||
//            !strcmp(cmd, "exit") ||
//            !strcmp(cmd, "export") ||
//            !strcmp(cmd, "unset") ||
//            !strcmp(cmd, "env"));
//}

//// 빌트인 실행
//int exec_builtin(t_cmd *cmd, t_env **env_list) {
//    if (!strcmp(cmd->argv[0], "echo")) {
//        int n_flag = 0, i = 1;
//        if (cmd->argc > 1 && strcmp(cmd->argv[1], "-n") == 0) {
//            n_flag = 1;
//            i = 2;
//        }
//        for (; i < cmd->argc; i++) {
//            printf("%s", cmd->argv[i]);
//            if (i < cmd->argc - 1) printf(" ");
//        }
//        if (!n_flag) printf("\n");
//        return 0;
//    }
//    else if (!strcmp(cmd->argv[0], "pwd")) {
//        char cwd[1024];
//        if (getcwd(cwd, sizeof(cwd)))
//            printf("%s\n", cwd);
//        else
//            perror("pwd");
//        return 0;
//    }
//    else if (!strcmp(cmd->argv[0], "cd")) {
//        const char *path = (cmd->argc > 1) ? cmd->argv[1] : get_env_value(*env_list, "HOME");
//        if (!path)
//            path = ".";
//        if (chdir(path) != 0) {
//            perror("cd");
//            return 1;
//        }
//        return 0;
//    }
//    else if (!strcmp(cmd->argv[0], "exit")) {
//        int status = 0;
//        if (cmd->argc > 1)
//            status = atoi(cmd->argv[1]);
//        printf("exit\n");
//        exit(status);
//    }
//    else if (!strcmp(cmd->argv[0], "env")) {
//        ms_env(*env_list);
//        return 0;
//    }
//    else if (!strcmp(cmd->argv[0], "export")) {
//        if (cmd->argc > 1) {
//            for (int i = 1; i < cmd->argc; i++)
//                ms_export(env_list, cmd->argv[i]);
//        }
//        return 0;
//    }
//    else if (!strcmp(cmd->argv[0], "unset")) {
//        if (cmd->argc > 1) {
//            for (int i = 1; i < cmd->argc; i++)
//                ms_unset(env_list, cmd->argv[i]);
//        }
//        return 0;
//    }
//    return -1;
//}

//// 외부 명령어 실행
//void exec_external(t_cmd *cmd) {
//    pid_t pid = fork();
//    if (pid == 0) {
//        execvp(cmd->argv[0], cmd->argv);
//        perror("execvp");
//        exit(1);
//    } else if (pid > 0) {
//        int status;
//        waitpid(pid, &status, 0);
//    } else {
//        perror("fork");
//    }
//}

//int main(int argc, char **argv, char **envp) {
//    t_env *env_list = init_env(envp);
//    char *line;

//    while ((line = readline("minishell$ ")) != NULL) {
//        if (*line)
//            add_history(line);

//        t_token tokens[MAX_TOKENS] = {0};
//        int token_count = parse_line(line, tokens);

//        if (token_count == 0) {
//            free(line);
//            continue;
//        }

//        t_cmd *cmd = create_cmd(tokens, token_count);

//        if (is_builtin(cmd->argv[0])) {
//            exec_builtin(cmd, &env_list);
//        } else {
//            exec_external(cmd);
//        }

//        for (int i = 0; i < token_count; i++)
//            free(tokens[i].str);
//        free_cmd(cmd);
//        free(line);
//    }
//    free_env(env_list);
//    return 0;
//}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <errno.h>

#define MAX_TOKENS 128
#define MAX_TOKEN_LEN 1024

typedef struct s_token {
    char *str;
} t_token;

typedef struct s_redir {
    char *type;           // ">", "<", ">>", "<<"
    char *file;
    struct s_redir *next;
} t_redir;

typedef struct s_cmd {
    char **argv;
    int argc;
    t_redir *redir;
    struct s_cmd *next;
} t_cmd;

// 토큰 추가
void add_token(t_token *tokens, int *count, char *buf, int len) {
    if (len <= 0) return;
    buf[len] = '\0';
    tokens[*count].str = strdup(buf);
    (*count)++;
}

// 토큰화
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

// 리다이렉션 구조체 생성/추가
t_redir *new_redir(char *type, char *file) {
    t_redir *redir = malloc(sizeof(t_redir));
    redir->type = strdup(type);
    redir->file = strdup(file);
    redir->next = NULL;
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

// 명령어 구조체 생성/추가
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

// 토큰 타입 판별
int is_redir(char *token) {
    return (!strcmp(token, ">") || !strcmp(token, "<") ||
            !strcmp(token, ">>") || !strcmp(token, "<<"));
}
int is_pipe(char *token) {
    return (!strcmp(token, "|"));
}

// 토큰 배열 → 명령어 구조체 리스트 변환
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

// 빌트인 명령어 판별
int is_builtin(const char *cmd) {
    return (!strcmp(cmd, "echo") ||
            !strcmp(cmd, "cd") ||
            !strcmp(cmd, "pwd") ||
            !strcmp(cmd, "exit"));
}

// 빌트인 명령어 실행 (echo, pwd, exit, cd)
int exec_builtin(t_cmd *cmd) {
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
        return 0;
    }
    else if (!strcmp(cmd->argv[0], "pwd")) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)))
            printf("%s\n", cwd);
        else
            perror("pwd");
        return 0;
    }
    else if (!strcmp(cmd->argv[0], "cd")) {
        const char *path = (cmd->argc > 1) ? cmd->argv[1] : getenv("HOME");
        if (!path)
            path = ".";
        if (chdir(path) != 0) {
            perror("cd");
            return 1;
        }
        return 0;
    }
    else if (!strcmp(cmd->argv[0], "exit")) {
        int status = 0;
        if (cmd->argc > 1)
            status = atoi(cmd->argv[1]);
        printf("exit\n");
        exit(status);
    }
    return -1;
}

// 외부 명령어 실행
void exec_external(t_cmd *cmd, char **envp) {
    pid_t pid = fork();
    if (pid == 0) {
        execvp(cmd->argv[0], cmd->argv);
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("fork");
    }
}

// 명령어 리스트 실행
void execute_cmd_list(t_cmd *cmd_list, char **envp) {
    while (cmd_list) {
        if (cmd_list->argc == 0) {
            cmd_list = cmd_list->next;
            continue;
        }
        if (is_builtin(cmd_list->argv[0])) {
            exec_builtin(cmd_list);
        } else {
            exec_external(cmd_list, envp);
        }
        cmd_list = cmd_list->next;
    }
}

// 메모리 해제
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
            free(redir);
            redir = next_redir;
        }
        free(cmd_list);
        cmd_list = next_cmd;
    }
}

int main(int argc, char **argv, char **envp) {
    char *line;
    while ((line = readline("minishell$ ")) != NULL) {
        if (*line)
            add_history(line);

        t_token tokens[MAX_TOKENS] = {0};
        int token_count = parse_line(line, tokens);

        t_cmd *cmd_list = create_cmd_list(tokens, token_count);

        execute_cmd_list(cmd_list, envp);

        for (int i = 0; i < token_count; i++)
            free(tokens[i].str);
        free_cmd_list(cmd_list);
        free(line);
    }
    return 0;
}




