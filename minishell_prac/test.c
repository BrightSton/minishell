/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 01:29:37 by djang             #+#    #+#             */
/*   Updated: 2025/04/28 01:29:39 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//#include <stdio.h>
//#include <readline/readline.h>
//#include <readline/history.h> // history 저장을 원할 경우

//int main(void)
//{
//    char *input;

//    while (1)
//    {
//        input = readline("minishell> ");
//        if (input == NULL) // Ctrl+D 입력 시 (EOF)
//        {
//            printf("exit\n");
//            break;
//        }
//        if (*input) // 입력이 비어있지 않으면
//            add_history(input); // 입력을 history에 추가 (옵션)
//        printf("You entered: %s\n", input);
//        free(input); // 메모리 해제
//    }
//    return 0;
//}

//#include <stdio.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//int main(void)
//{
//    char *input;

//    while (1)
//    {
//        input = readline("minishell> ");
//        if (input == NULL)
//        {
//            printf("exit\n");
//            break;
//        }
//        if (*input)
//            add_history(input);

//        printf("You entered: %s\n", input);
//        free(input);
//    }

//    rl_clear_history(); // 프로그램 끝날 때 history 정리
//    return 0;
//}


//int main(void)
//{
//    char *input;

//    while (1)
//    {
//        input = readline("minishell> ");
//        if (input == NULL)
//        {
//            printf("exit\n");
//            break;
//        }
//        if (*input)
//            add_history(input);

//        if (strcmp(input, "clear") == 0)
//        {
//            rl_clear_history();
//            printf("History cleared!\n");
//        }

//        free(input);
//    }
//    return 0;
//}

//#include <stdio.h>
//#include <readline/readline.h>
//#include <readline/history.h>
//#include <signal.h>

//void handler(int sig)
//{
//    (void)sig;
//    printf("\n"); // 새 줄 출력
//    rl_on_new_line();      // readline에 "새 줄이야" 알리기
//    rl_replace_line("", 0); // 입력 줄 비우기 (옵션)
//    rl_redisplay();        // 입력줄 다시 보여주기
//}

//int main(void)
//{
//    char *input;

//    signal(SIGINT, handler); // Ctrl+C 누르면 handler 호출

//    while (1)
//    {
//        input = readline("minishell> ");
//        if (input == NULL)
//        {
//            printf("exit\n");
//            break;
//        }
//        if (*input)
//            add_history(input);

//        free(input);
//    }
//    rl_clear_history();
//    return 0;
//}

//#include <stdio.h>
//#include <readline/readline.h>
//#include <readline/history.h>
//#include <signal.h>

//void handler(int sig)
//{
//    (void)sig;
//    printf("\n"); // 줄 넘기고
//    rl_on_new_line();              // 새 줄 시작 알리고
//    rl_replace_line("You pressed Ctrl+C", 0); // 입력줄 교체
//    rl_redisplay();                // 새 입력줄 출력
//}

//int main(void)
//{
//    char *input;

//    signal(SIGINT, handler); // Ctrl+C 핸들러 등록

//    while (1)
//    {
//        input = readline("minishell> ");
//        if (input == NULL)
//        {
//            printf("exit\n");
//            break;
//        }
//        if (*input)
//            add_history(input);

//        free(input);
//    }
//    rl_clear_history();
//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>

//int main(void)
//{
//    if (access("/bin/ls", X_OK) == 0)
//        printf("'/bin/ls' is executable.\n");
//    else
//        printf("'/bin/ls' is not executable.\n");

//    if (access("/etc/passwd", R_OK) == 0)
//        printf("'/etc/passwd' is readable.\n");
//    else
//        printf("'/etc/passwd' is not readable.\n");

//    if (access("somefile.txt", F_OK) == 0)
//        printf("'somefile.txt' exists.\n");
//    else
//        printf("'somefile.txt' does not exist.\n");

//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>

//int main(void)
//{
//    pid_t pid;

//    pid = fork();

//    if (pid < 0)
//    {
//        perror("fork failed");
//        return 1;
//    }
//    else if (pid == 0)
//    {
//        printf("I'm the child process!\n");
//    }
//    else
//    {
//        printf("I'm the parent process! Child PID: %d\n", pid);
//    }

//    return 0;
//}


//#include <stdio.h>
//#include <unistd.h>
//#include <sys/wait.h>

//int main(void)
//{
//    pid_t pid;
//    int status;

//    pid = fork();
//    if (pid == -1)
//    {
//        perror("fork failed");
//        return 1;
//    }
//    else if (pid == 0)
//    {
//        printf("Child: Hello!\n");
//    }
//    else
//    {
//        wait(&status); // 자식이 종료될 때까지 부모는 대기
//        printf("Parent: Child process has finished.\n");
//    }

//    return 0;
//}


//#include <stdio.h>
//#include <unistd.h>
//#include <sys/wait.h>

//int main(void)
//{
//    pid_t pid;
//    int status;

//    pid = fork();
//    if (pid == -1)
//    {
//        perror("fork failed");
//        return 1;
//    }
//    else if (pid == 0)
//    {
//        printf("Child: I'm alive!\n");
//    }
//    else
//    {
//        waitpid(pid, &status, 0); // 특정 자식(pid)을 기다린다
//        if (WIFEXITED(status))
//            printf("Parent: Child exited with code %d\n", WEXITSTATUS(status));
//    }
//    return 0;
//}


//#include <stdio.h>
//#include <sys/wait.h>
//#include <sys/resource.h>
//#include <unistd.h>

//int main(void)
//{
//    pid_t pid;
//    int status;
//    struct rusage usage;

//    pid = fork();
//    if (pid == -1)
//    {
//        perror("fork failed");
//        return 1;
//    }
//    else if (pid == 0)
//    {
//        for (volatile long i = 0; i < 100000000; i++); // CPU 사용
//        _exit(0);
//    }
//    else
//    {
//        wait3(&status, 0, &usage);

//        if (WIFEXITED(status))
//            printf("Child exited with code %d\n", WEXITSTATUS(status));

//        printf("User CPU time used: %ld.%06ld seconds\n", 
//               usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
//        printf("System CPU time used: %ld.%06ld seconds\n", 
//               usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
//    }
//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>
//#include <sys/wait.h>
//#include <sys/resource.h>

//int main(void)
//{
//    pid_t pid;
//    int status;
//    struct rusage usage;

//    pid = fork();
//    if (pid == -1)
//    {
//        perror("fork failed");
//        return 1;
//    }
//    else if (pid == 0)
//    {
//        for (volatile long i = 0; i < 100000000; i++); // CPU 많이 쓰기
//        _exit(42);
//    }
//    else
//    {
//        wait4(pid, &status, 0, &usage);

//        if (WIFEXITED(status))
//            printf("Child exited with code %d\n", WEXITSTATUS(status));

//        printf("User CPU time: %ld.%06ld sec\n",
//               usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
//        printf("System CPU time: %ld.%06ld sec\n",
//               usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
//    }
//    return 0;
//}

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//void sigint_handler(int sig)
//{
//    (void)sig;
//    printf("\nCtrl+C pressed. SIGINT caught!\n");
//}

//int main(void)
//{
//    signal(SIGINT, sigint_handler); // Ctrl+C 누르면 sigint_handler 실행

//    while (1)
//    {
//        printf("Running...\n");
//        sleep(1);
//    }
//    return 0;
//}

//#include <stdio.h>
//#include <signal.h>
//#include <unistd.h>

//void sigint_handler(int sig)
//{
//    (void)sig;
//    printf("\nCaught SIGINT (Ctrl+C)\n");
//}

//int main(void)
//{
//    struct sigaction sa;
    

//    sa.sa_handler = sigint_handler; // 핸들러 함수 설정
//    sigemptyset(&sa.sa_mask);        // 시그널 핸들 중 block할 시그널 없음
//    sa.sa_flags = 0;                 // 특별한 플래그 없음

//    sigaction(SIGINT, &sa, NULL); // SIGINT에 대해 설정

//    while (1)
//    {
//        printf("Running...\n");
//        sleep(1);
//    }
//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>
//#include <stdlib.h>

//int main(void)
//{
//    char *cwd = getcwd(NULL, 0); // 알아서 메모리 할당
//    if (cwd != NULL)
//    {
//        printf("Current directory: %s\n", cwd);
//        free(cwd); // 직접 free 해줘야 한다
//    }
//    else
//        perror("getcwd failed");

//    return 0;
//}
//#include <stdio.h>
//#include <unistd.h>

//int main(void)
//{
//    if (chdir("/tmp") != 0)
//    {
//        perror("chdir failed");
//        return 1;
//    }

//    printf("Changed directory to /tmp\n");
//    return 0;
//}

//#include <stdio.h>
//#include <sys/stat.h>
//#include <unistd.h>

//int main(void)
//{
//    struct stat st;

//    if (stat("test.txt", &st) == 0)
//    {
//        printf("File size: %ld bytes\n", st.st_size);

//        if (S_ISDIR(st.st_mode))
//            printf("It is a directory.\n");
//        else if (S_ISREG(st.st_mode))
//            printf("It is a regular file.\n");
//    }
//    else
//    {
//        perror("stat failed");
//    }

//    return 0;
//}

//int main(void)
//{
//    struct stat st;

//    if (lstat("mylink", &st) == 0)
//    {
//        if (S_ISLNK(st.st_mode))
//            printf("It is a symbolic link!\n");
//        else if (S_ISREG(st.st_mode))
//            printf("It is a regular file.\n");
//        else if (S_ISDIR(st.st_mode))
//            printf("It is a directory.\n");
//    }
//    else
//    {
//        perror("lstat failed");
//    }

//    return 0;
//}

//#include <stdio.h>
//#include <fcntl.h>
//#include <unistd.h>
//#include <sys/stat.h>

//int main(void)
//{
//    struct stat st;
//    int fd = open("test.txt", O_RDONLY);

//    if (fd == -1)
//    {
//        perror("open failed");
//        return 1;
//    }

//    if (fstat(fd, &st) == 0)
//    {
//        printf("File size: %ld bytes\n", st.st_size);
//    }
//    else
//    {
//        perror("fstat failed");
//    }

//    close(fd);
//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>

//int main(void)
//{
//    if (unlink("test.txt") == 0)
//    {
//        printf("File deleted successfully.\n");
//    }
//    else
//    {
//        perror("unlink failed");
//    }
//    return 0;
//}

#include <unistd.h>
#include <stdio.h>

//int main(void)
//{
//    char *argv[] = { "ls", "-l", NULL };
//    char *envp[] = { NULL }; // 기본 환경변수 (간단 예시)

//    if (execve("/bin/ls", argv, envp) == -1)
//    {
//        perror("execve failed");
//        return 1;
//    }

//    // 여기는 절대 실행되지 않음 (성공하면 덮어쓰니까)
//    return 0;
//}

//int main(void)
//{
//    char *argv[] = { "ls", "-al", NULL };
//    char *envp[] = { NULL }; // 기본 환경변수 (간단 예시)

//    pid_t pid = fork();
//    if (pid == 0)
//    {
//        // 자식 프로세스
//        execve("/bin/ls", argv, envp);
//        // 실패했으면 여기 도달
//        perror("execve failed");
//        exit(1);
//    }
//    else if (pid > 0)
//    {
//        // 부모 프로세스
//        waitpid(pid, NULL, 0);
//    }
//    else
//    {
//        perror("fork failed");
//    }
//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>
//#include <fcntl.h>

//int main(void)
//{
//    int fd = open("file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//    if (fd == -1)
//        return 1;

//    int copy_fd = dup(fd);
//    if (copy_fd == -1)
//        return 1;

//    write(copy_fd, "Hello, dup!\n", 12);

//    close(fd);
//    close(copy_fd);
//    return 0;
//}

//#include <fcntl.h>
//#include <unistd.h>
//#include <stdio.h>

//int main(void)
//{
//    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//    if (fd == -1)
//        return 1;

//    dup2(fd, STDOUT_FILENO); // 표준 출력을 output.txt로 덮어쓰기

//    printf("This goes to the file!\n");

//    close(fd);
//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>

//int main(void)
//{
//    int pipefd[2];
//    char buf[20];

//    if (pipe(pipefd) == -1)
//    {
//        perror("pipe failed");
//        return 1;
//    }

//    write(pipefd[1], "hello pipe\n", 11);
//    read(pipefd[0], buf, 11);

//    printf("Received: %s", buf);

//    close(pipefd[0]);
//    close(pipefd[1]);

//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>
//#include <sys/wait.h>

//int main(void)
//{
//    int pipefd[2];
//    pid_t pid;

//    if (pipe(pipefd) == -1)
//    {
//        perror("pipe failed");
//        return 1;
//    }

//    pid = fork();
//    if (pid == -1)
//    {
//        perror("fork failed");
//        return 1;
//    }

//    if (pid == 0)
//    {
//        // 자식 프로세스
//        close(pipefd[1]); // 쓰기 쪽 닫기
//        dup2(pipefd[0], STDIN_FILENO); // 읽기 쪽을 표준입력으로 연결
//        close(pipefd[0]); // 연결 끝났으면 닫기
//        execlp("grep", "grep", "foo", NULL);
//        // exec 실패하면
//        perror("execlp failed");
//        return 1;
//    }
//    else
//    {
//        // 부모 프로세스
//        close(pipefd[0]); // 읽기 쪽 닫기
//        write(pipefd[1], "foo\nbar\nbaz\n", 12);
//        close(pipefd[1]); // 쓰기 끝났으면 닫기
//        waitpid(pid, NULL, 0);
//    }

//    return 0;
//}

//#include <stdio.h>
//#include <dirent.h>

//int main(void)
//{
//    DIR *dir = opendir(".");
//    if (dir == NULL)
//    {
//        perror("opendir failed");
//        return 1;
//    }

//    printf("Directory opened successfully!\n");

//    closedir(dir); // 디렉토리 닫기
//    return 0;
//}

//#include <stdio.h>
//#include <dirent.h>

//int main(void)
//{
//    DIR *dir = opendir(".");
//    struct dirent *entry;

//    if (!dir)
//    {
//        perror("opendir failed");
//        return 1;
//    }

//    while ((entry = readdir(dir)) != NULL)
//    {
//        printf("%s\n", entry->d_name); // 파일/디렉토리 이름 출력
//    }

//    closedir(dir);
//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>

//int main(void)
//{
//    if (isatty(STDIN_FILENO))
//        printf("stdin은 터미널입니다!\n");
//    else
//        printf("stdin은 터미널이 아닙니다!\n");

//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>

//int main(void)
//{
//    char *name = ttyname(STDIN_FILENO);

//    if (name)
//        printf("stdin이 연결된 터미널은: %s\n", name);
//    else
//        perror("ttyname");

//    return 0;
//}

//#include <stdio.h>
//#include <unistd.h>

//int main(void)
//{
//    int slot = ttyslot();

//    if (slot > 0)
//        printf("현재 터미널 슬롯 번호: %d\n", slot);
//    else
//        printf("터미널 슬롯 찾기 실패\n");

//    return 0;
//}

//#include <stdio.h>
//#include <stdlib.h>

//int main(void)
//{
//    char *home = getenv("HOME");

//    if (home)
//        printf("HOME = %s\n", home);
//    else
//        printf("HOME 환경변수가 없습니다.\n");

//    return 0;
//}

//#include <stdio.h>
//#include <termios.h>
//#include <unistd.h>

//int main(void)
//{
//    struct termios old, new;

//    // 현재 터미널 속성 가져오기
//    tcgetattr(STDIN_FILENO, &old);

//    new = old;
//    new.c_lflag &= ~(ICANON | ECHO);  // Canonical 모드 끄고, 에코 끄기

//    // 변경 적용
//    tcsetattr(STDIN_FILENO, TCSANOW, &new);

//    printf("non-canonical 모드로 전환. 입력해보세요 (Ctrl+D로 종료).\n");

//    int c;
//    while (1)
//    {
//        c = getchar();
//        if (c == 4) // Ctrl+D는 ASCII 4 (EOT)
//            break;
//        printf("입력한 문자: %c\n", c);
//    }

//    // 원래 모드로 복구
//    tcsetattr(STDIN_FILENO, TCSANOW, &old);

//    printf("\n터미널 모드 복구 완료\n");
//    return 0;
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <term.h>

//int main(void)
//{
//    if (tgetent(NULL, getenv("TERM")) != 1)
//    {
//        printf("터미널 정보 불러오기 실패\n");
//        return 1;
//    }

//    if (tgetflag("am"))  // am: 자동 줄바꿈(Automatic Margins)
//        printf("이 터미널은 자동 줄바꿈을 지원합니다.\n");
//    else
//        printf("이 터미널은 자동 줄바꿈을 지원하지 않습니다.\n");

//    return 0;
//}

//#include <stdio.h>
//#include <stdlib.h>
//#include <term.h>
//#include <unistd.h>

//int main(void)
//{
//    if (tgetent(NULL, getenv("TERM")) != 1)
//    {
//        perror("tgetent");
//        return 1;
//    }

//    clear_screen = tgetstr("cl", NULL);
//    if (clear_screen)
//        tputs(clear_screen, 1, putchar);

//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <unistd.h>

int main(void)
{
    if (tgetent(NULL, getenv("TERM")) != 1)
    {
        perror("tgetent");
        return 1;
    }

    char *cm = tgetstr("cm", NULL);  // "cm" = 커서 이동 포맷
    if (cm == NULL)
    {
        printf("커서 이동 기능을 지원하지 않습니다.\n");
        return 1;
    }

    char *move = tgoto(cm, 10, 5);   // (x=10, y=5)로 이동할 시퀀스 생성
    tputs(move, 1, putchar);

    printf("커서가 (10, 5)로 이동했습니다.\n");

    return 0;
}