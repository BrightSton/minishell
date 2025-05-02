/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 20:30:20 by djang             #+#    #+#             */
/*   Updated: 2025/04/29 20:30:22 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// minishell.c
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <sys/wait.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//void execute_command(char *input)
//{
//    pid_t pid;
//    char *argv[2];

//    pid = fork();
//    if (pid < 0)
//    {
//        perror("fork failed");
//        return;
//    }
//    else if (pid == 0)
//    {
//        // 자식 프로세스
//        argv[0] = input; // 명령어
//        argv[1] = NULL;  // execve는 마지막 인자가 NULL이어야 함
//        if (execvp(argv[0], argv) == -1) // PATH 검색까지 해주는 execvp
//        {
//            perror("execvp failed");
//            exit(EXIT_FAILURE);
//        }
//    }
//    else
//    {
//        // 부모 프로세스
//        waitpid(pid, NULL, 0);
//    }
//}

//int main(void)
//{
//    char *input;

//    while (1)
//    {
//        input = readline("minishell$ ");
//        if (!input)
//        {
//            printf("\nexit\n");
//            break;
//        }

//        if (strlen(input) > 0)
//            add_history(input);

//        if (strcmp(input, "exit") == 0)
//        {
//            free(input);
//            printf("exit\n");
//            break;
//        }

//        if (strlen(input) > 0)
//            execute_command(input);

//        free(input);
//    }

//    return 0;
//}


//// minishell.c
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <sys/wait.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//char **split_input(char *input)
//{
//    char **argv = NULL;
//    char *token;
//    int argc = 0;

//    argv = malloc(sizeof(char *) * 100); // 임시로 최대 100개 인자
//    if (!argv)
//    {
//        perror("malloc failed");
//        exit(EXIT_FAILURE);
//    }

//    token = strtok(input, " ");
//    while (token)
//    {
//        argv[argc++] = strdup(token); // strdup는 메모리 복사
//        token = strtok(NULL, " ");
//    }
//    argv[argc] = NULL;
//    return argv;
//}

//void free_argv(char **argv)
//{
//    int i = 0;
//    while (argv[i])
//        free(argv[i++]);
//    free(argv);
//}

//void execute_command(char *input)
//{
//    pid_t pid;
//    char **argv;

//    argv = split_input(input);

//    pid = fork();
//    if (pid < 0)
//    {
//        perror("fork failed");
//        free_argv(argv);
//        return;
//    }
//    else if (pid == 0)
//    {
//        if (execvp(argv[0], argv) == -1)
//        {
//            perror("execvp failed");
//            exit(EXIT_FAILURE);
//        }
//    }
//    else
//    {
//        waitpid(pid, NULL, 0);
//    }

//    free_argv(argv);
//}

//int main(void)
//{
//    char *input;

//    while (1)
//    {
//        input = readline("minishell$ ");
//        if (!input)
//        {
//            printf("\nexit\n");
//            break;
//        }

//        if (strlen(input) > 0)
//            add_history(input);

//        if (strcmp(input, "exit") == 0)
//        {
//            free(input);
//            printf("exit\n");
//            break;
//        }

//        if (strlen(input) > 0)
//            execute_command(input);

//        free(input);
//    }

//    return 0;
//}

// minishell_pipe.c
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <string.h>
//#include <sys/wait.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//char **split_input(char *input, const char *delimiter)
//{
//    char **argv = NULL;
//    char *token;
//    int argc = 0;

//    argv = malloc(sizeof(char *) * 100); // 최대 100개
//    if (!argv)
//    {
//        perror("malloc failed");
//        exit(EXIT_FAILURE);
//    }

//    token = strtok(input, delimiter);
//    while (token)
//    {
//        argv[argc++] = strdup(token);
//        token = strtok(NULL, delimiter);
//    }
//    argv[argc] = NULL;
//    return argv;
//}

//void free_argv(char **argv)
//{
//    int i = 0;
//    while (argv[i])
//        free(argv[i++]);
//    free(argv);
//}

//void execute_piped_commands(char *input)
//{
//    int pipefd[2];
//    pid_t pid1, pid2;
//    char **cmd1;
//    char **cmd2;

//    char **commands = split_input(input, "|");
//    if (!commands[0] || !commands[1])
//    {
//        printf("invalid command\n");
//        free_argv(commands);
//        return;
//    }

//    cmd1 = split_input(commands[0], " ");
//    cmd2 = split_input(commands[1], " ");

//    if (pipe(pipefd) == -1)
//    {
//        perror("pipe failed");
//        free_argv(cmd1);
//        free_argv(cmd2);
//        free_argv(commands);
//        return;
//    }

//    pid1 = fork();
//    if (pid1 == 0)
//    {
//        // 1번 명령어 실행
//        dup2(pipefd[1], STDOUT_FILENO);
//        close(pipefd[0]);
//        close(pipefd[1]);
//        if (execvp(cmd1[0], cmd1) == -1)
//        {
//            perror("execvp failed (first cmd)");
//            exit(EXIT_FAILURE);
//        }
//    }

//    pid2 = fork();
//    if (pid2 == 0)
//    {
//        // 2번 명령어 실행
//        dup2(pipefd[0], STDIN_FILENO);
//        close(pipefd[1]);
//        close(pipefd[0]);
//        if (execvp(cmd2[0], cmd2) == -1)
//        {
//            perror("execvp failed (second cmd)");
//            exit(EXIT_FAILURE);
//        }
//    }

//    // 부모 프로세스
//    close(pipefd[0]);
//    close(pipefd[1]);
//    waitpid(pid1, NULL, 0);
//    waitpid(pid2, NULL, 0);

//    free_argv(cmd1);
//    free_argv(cmd2);
//    free_argv(commands);
//}

//int main(void)
//{
//    char *input;

//    while (1)
//    {
//        input = readline("minishell$ ");
//        if (!input)
//        {
//            printf("\nexit\n");
//            break;
//        }

//        if (strlen(input) > 0)
//            add_history(input);

//        if (strcmp(input, "exit") == 0)
//        {
//            free(input);
//            printf("exit\n");
//            break;
//        }

//        if (strchr(input, '|'))
//            execute_piped_commands(input);
//        else
//            execute_piped_commands(input); // TODO: 분리 필요 (단일 명령어 실행 함수 만들기)

//        free(input);
//    }

//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

char **split_input(char *input, const char *delimiter)
{
    char **argv = malloc(sizeof(char *) * 100);
    char *token;
    int argc = 0;

    token = strtok(input, delimiter);
    while (token)
    {
        argv[argc++] = strdup(token);
        token = strtok(NULL, delimiter);
    }
    argv[argc] = NULL;
    return argv;
}

void free_argv(char **argv)
{
    int i = 0;
    while (argv[i])
        free(argv[i++]);
    free(argv);
}

void execute_single_command(char *input)
{
    pid_t pid;
    char **cmd = split_input(input, " ");

    pid = fork();
    if (pid == 0)
    {
        execvp(cmd[0], cmd);
        perror("execvp failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
    free_argv(cmd);
}

void execute_piped_commands(char *input)
{
    int pipefd[2];
    pid_t pid1, pid2;
    char **cmds = split_input(input, "|");

    if (!cmds[0] || !cmds[1])
    {
        printf("Invalid input.\n");
        free_argv(cmds);
        return;
    }

    char **cmd1 = split_input(cmds[0], " ");
    char **cmd2 = split_input(cmds[1], " ");

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid1 = fork();
    if (pid1 == 0)
    {
        // 첫 번째 명령어 실행
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);
        execvp(cmd1[0], cmd1);
        perror("execvp first command");
        exit(EXIT_FAILURE);
    }

    pid2 = fork();
    if (pid2 == 0)
    {
        // 두 번째 명령어 실행
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        execvp(cmd2[0], cmd2);
        perror("execvp second command");
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    free_argv(cmd1);
    free_argv(cmd2);
    free_argv(cmds);
}

int main(void)
{
    char *input;

    while (1)
    {
        input = readline("minishell$ ");
        if (!input)
        {
            printf("\nexit\n");
            break;
        }
        if (strcmp(input, "exit") == 0)
        {
            free(input);
            printf("exit\n");
            break;
        }
        if (strlen(input) > 0)
            add_history(input);

        if (strchr(input, '|'))
            execute_piped_commands(input);
        else
            execute_single_command(input); // 여기 수정!!!

        free(input);
    }

    return 0;
}

