/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 00:27:21 by djang             #+#    #+#             */
/*   Updated: 2025/05/01 00:27:22 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <readline/readline.h>
//#include <readline/history.h>

//char *here_doc_read(const char *limiter) {
//    size_t size = 0;
//    char *result = NULL;
//    while (1) {
//        char *line = readline("> ");
//        if (!line || strcmp(line, limiter) == 0) {
//            free(line);
//            break;
//        }
//        size_t len = strlen(line);
//        result = realloc(result, size + len + 2);
//        memcpy(result + size, line, len);
//        size += len;
//        result[size++] = '\n';
//        result[size] = 0;
//        free(line);
//    }
//    return result;
//}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>

// 히어독을 임시파일에 저장하고, 그 파일의 fd를 반환
int heredoc_to_tmpfile(const char *limiter) {
    char tmpname[] = "/tmp/minishell_heredocXXXXXX";
    int fd = mkstemp(tmpname);
    if (fd < 0) {
        perror("mkstemp");
        return -1;
    }
    unlink(tmpname); // 임시파일 자동 삭제

    while (1) {
        char *line = readline("> ");
        if (!line || strcmp(line, limiter) == 0) {
            free(line);
            break;
        }
        write(fd, line, strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    lseek(fd, 0, SEEK_SET); // 파일 포인터 처음으로
    return fd;
}

int main(void) {
    printf("예시: cat << EOF\n");
    printf("EOF를 입력할 때까지 여러 줄을 입력하세요.\n");

    int fd = heredoc_to_tmpfile("EOF");
    if (fd < 0) return 1;

    // cat처럼 STDIN을 임시파일로 연결해서 출력
    char buf[1024];
    ssize_t n;
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        write(STDOUT_FILENO, buf, n);
    }
    close(fd);
    return 0;
}
