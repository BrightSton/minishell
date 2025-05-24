/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 23:43:54 by djang             #+#    #+#             */
/*   Updated: 2025/05/18 23:43:56 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


static void	apply_redir(t_cmd *cmd)
{
	t_redir	*r;
	int		fd;

	r = cmd->redir;
	while (r)
	{
		if (!r->file || !r->file[0])
		{
			printf("minishell: syntax error near unexpected token\n");
			_exit(1);
		}

		if(r->type == TK_REDIR_IN)
		{
			fd = open(r->file,O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				_exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else if (r->type == TK_REDIR_OUT)
		{
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
			{
				perror("open");
				_exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		// (TK_REDIR_APPEND, TK_HEREDOC 등은 추후 추가)
		else if (r->type == TK_REDIR_APPEND)
		{
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd < 0)
			{
				perror("open");
				_exit(1);
			}
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else if (r->type == TK_HEREDOC)
		{
			fd = open(r->file, O_RDONLY);
			if (fd < 0)
			{
				perror("open");
				_exit(1);
			}
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		r = r->next;
	}
}


//void	execute_cmd(t_cmd *cmd)
//{
	
//	pid_t	pid;
//	int		status;

//	if (!cmd || !cmd->argv || !cmd->argv[0] || !*cmd->argv[0])
//		return ;
//	pid = fork();
//	if (pid < 0)
//	{
//		perror("fork");
//		return ;
//	}
//	if (pid == 0)
//	{
//		apply_redir(cmd);
//		execvp(cmd->argv[0], cmd->argv);
//		perror("execvp");
//		_exit(1);
//	}
//	else
//	{
//		waitpid(pid, &status, 0);
//	}
//}

//void	execute_cmd(t_cmd *cmd)
//{
//	int		pipefd[2];
//	int		prev_read;
//	pid_t	pid;
//	int		is_last;

//	prev_read = -1;
//	while (cmd)
//	{
//		is_last = (cmd->next == NULL);
//		if (!is_last)
//		{
//			if (pipe(pipefd) < 0)
//			{
//				perror("pipe");
//				return ;
//			}
//		}
//		pid = fork();
//		if (pid < 0)
//		{
//			perror("fork");
//			return ;
//		}
//		if (pid == 0)
//		{
//			// 리다이렉션(입출력 파일) 적용
//			apply_redir(cmd);

//			// stdin 연결: 이전 파이프 read end
//			if (prev_read != -1)
//			{
//				dup2(prev_read, 0);
//				close(prev_read);
//			}
//			// stdout 연결: 다음 파이프 write end
//			if (!is_last)
//			{
//				dup2(pipefd[1], 1);
//				close(pipefd[0]);
//				close(pipefd[1]);
//			}
//			execvp(cmd->argv[0], cmd->argv);
//			perror("execvp");
//			_exit(1);
//		}
//		// 부모 프로세스 fd 정리
//		if (prev_read != -1)
//			close(prev_read);
//		if (!is_last)
//		{
//			close(pipefd[1]);
//			prev_read = pipefd[0];
//		}
//		cmd = cmd->next;
//	}
//	while (wait(NULL) > 0)
//		;
//}



//void	execute_cmd(t_cmd *cmd, t_shell *shell)
//{
//	int		pipefd[2];
//	int		prev_read;
//	pid_t	pid;
//	int		is_last;
//	int		status;

//	prev_read = -1;
//	while (cmd)
//	{
//		is_last = (cmd->next == NULL);
//		if (!cmd->argv || !cmd->argv[0])
//		{
//			cmd = cmd->next;
//			continue;
//		}
//		if (!is_last)
//		{
//			if (pipe(pipefd) < 0)
//			{
//				perror("pipe");
//				return;
//			}
//		}
//		pid = fork();
//		if (pid < 0)
//		{
//			perror("fork");
//			return;
//		}
//		if (pid == 0)
//		{
//			apply_redir(cmd);
//			if (prev_read != -1)
//			{
//				dup2(prev_read, 0);
//				close(prev_read);
//			}
//			if (!is_last)
//			{
//				dup2(pipefd[1], 1);
//				close(pipefd[0]);
//				close(pipefd[1]);
//			}
//			execvp(cmd->argv[0], cmd->argv);
//			perror("execvp");
//			_exit(1);
//		}
//		if (prev_read != -1)
//			close(prev_read);
//		if (!is_last)
//		{
//			close(pipefd[1]);
//			prev_read = pipefd[0];
//		}
//		cmd = cmd->next;
//	}
//	while (wait(&status) > 0)
//	{
//		if (WIFEXITED(status))
//			shell->last_exit_status = WEXITSTATUS(status);
//		else if (WIFSIGNALED(status))
//			shell->last_exit_status = 128 + WTERMSIG(status);
//	}
//}

//void execute_cmd(t_cmd *cmd, t_shell *shell)
//{
//    int pipefd[2];
//    int prev_read;
//    pid_t pid;
//    int is_last;
//    int status;

//    prev_read = -1;
//    while (cmd)
//    {
//        is_last = (cmd->next == NULL);
        
//        // 명령어가 없는 경우 스킵
//        if (!cmd->argv || !cmd->argv[0])
//        {
//            cmd = cmd->next;
//            continue;
//        }
        
//        // 빌트인 명령어 처리 (파이프가 없는 경우에만)
//        if (is_last && prev_read == -1 && is_builtin(cmd->argv[0]))
//        {
//            shell->last_exit_status = execute_builtin(cmd, shell);
//            cmd = cmd->next;
//            continue;
//        }
        
//        if (!is_last)
//        {
//            if (pipe(pipefd) < 0)
//            {
//                perror("pipe");
//                return;
//            }
//        }
        
//        pid = fork();
//        if (pid < 0)
//        {
//            perror("fork");
//            return;
//        }
        
//        if (pid == 0)
//        {
//            // 리다이렉션 적용
//            apply_redir(cmd);
            
//            // stdin 연결: 이전 파이프 read end
//            if (prev_read != -1)
//            {
//                dup2(prev_read, 0);
//                close(prev_read);
//            }
            
//            // stdout 연결: 다음 파이프 write end
//            if (!is_last)
//            {
//                dup2(pipefd[1], 1);
//                close(pipefd[0]);
//                close(pipefd[1]);
//            }
            
//            // 빌트인 명령어 처리
//            if (is_builtin(cmd->argv[0]))
//            {
//                exit(execute_builtin(cmd, shell));
//            }
            
//            execvp(cmd->argv[0], cmd->argv);
//            perror("execvp");
//            _exit(1);
//        }
        
//        // 부모 프로세스 fd 정리
//        if (prev_read != -1)
//            close(prev_read);
//        if (!is_last)
//        {
//            close(pipefd[1]);
//            prev_read = pipefd[0];
//        }
        
//        cmd = cmd->next;
//    }
    
//    // 모든 자식 프로세스 대기
//    while (wait(&status) > 0)
//    {
//        if (WIFEXITED(status))
//            shell->last_exit_status = WEXITSTATUS(status);
//        else if (WIFSIGNALED(status))
//            shell->last_exit_status = 128 + WTERMSIG(status);
//    }
//}


// 아래 수정필요
//void execute_cmd(t_cmd *cmd, t_shell *shell)
//{
//    int pipefd[2];
//    int prev_read;
//    pid_t pid;
//    int is_last;
//    int status;
//    t_cmd *current;

//    // 히어독 처리
//    current = cmd;
//    while (current)
//    {
//        handle_heredoc(current);
//        current = current->next;
//    }

//    prev_read = -1;
//    while (cmd)
//    {
//        is_last = (cmd->next == NULL);
        
//        // 명령어가 없는 경우 스킵
//        if (!cmd->argv || !cmd->argv[0])
//        {
//            cmd = cmd->next;
//            continue;
//        }
        
//        // 빌트인 명령어 처리 (파이프가 없는 경우에만)
//        if (is_last && prev_read == -1 && is_builtin(cmd->argv[0]))
//        {
//            shell->last_exit_status = execute_builtin(cmd, shell);
//            cmd = cmd->next;
//            continue;
//        }
        
//        if (!is_last)
//        {
//            if (pipe(pipefd) < 0)
//            {
//                perror("pipe");
//                return;
//            }
//        }
        
//        pid = fork();
//        if (pid < 0)
//        {
//            perror("fork");
//            return;
//        }
        
//        if (pid == 0)
//        {
//            // 자식 프로세스에서 시그널 핸들러 재설정
//            signal(SIGINT, SIG_DFL);
//            signal(SIGQUIT, SIG_DFL);
            
//            // 리다이렉션 적용
//            apply_redir(cmd);
            
//            // stdin 연결: 이전 파이프 read end
//            if (prev_read != -1)
//            {
//                dup2(prev_read, 0);
//                close(prev_read);
//            }
            
//            // stdout 연결: 다음 파이프 write end
//            if (!is_last)
//            {
//                dup2(pipefd[1], 1);
//                close(pipefd[0]);
//                close(pipefd[1]);
//            }
            
//            // 빌트인 명령어 처리
//            if (is_builtin(cmd->argv[0]))
//            {
//                exit(execute_builtin(cmd, shell));
//            }
            
//            execvp(cmd->argv[0], cmd->argv);
//            perror("execvp");
//            _exit(1);
//        }
        
//        // 부모 프로세스 fd 정리
//        if (prev_read != -1)
//            close(prev_read);
//        if (!is_last)
//        {
//            close(pipefd[1]);
//            prev_read = pipefd[0];
//        }
        
//        cmd = cmd->next;
//    }
    
//    // 모든 자식 프로세스 대기
//    while (wait(&status) > 0)
//    {
//        if (WIFEXITED(status))
//            shell->last_exit_status = WEXITSTATUS(status);
//        else if (WIFSIGNALED(status))
//            shell->last_exit_status = 128 + WTERMSIG(status);
//    }
//}

void	execute_cmd(t_cmd *cmd, t_shell *shell)
{
	int		pipefd[2];
	int		prev_read;
	pid_t	pid;
	int		is_last;
	int		status;
	t_cmd	*current;

	// 히어독 처리
	current = cmd;
	while (current)
	{
		handle_heredoc(current);
		current = current->next;
	}

	prev_read = -1;
	while (cmd)
	{
		is_last = (cmd->next == NULL);
		
		// 명령어가 없는 경우 스킵
		if (!cmd->argv || !cmd->argv[0])
		{
			cmd = cmd->next;
			continue;
		}
		
		// 빌트인 명령어 처리 (파이프가 없는 경우에만)
		if (is_last && prev_read == -1 && !cmd->redir && is_builtin(cmd->argv[0]))
		{
			shell->last_exit_status = execute_builtin(cmd, shell);
			cmd = cmd->next;
			continue;
		}
		
		if (!is_last)
		{
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				return;
			}
		}
		
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return;
		}
		
		if (pid == 0)
		{
			// 자식 프로세스에서 시그널 핸들러 재설정
			set_signal_child();
			
			// 리다이렉션 적용
			apply_redir(cmd);
			
			// stdin 연결: 이전 파이프 read end
			if (prev_read != -1)
			{
				dup2(prev_read, 0);
				close(prev_read);
			}
			
			// stdout 연결: 다음 파이프 write end
			if (!is_last)
			{
				dup2(pipefd[1], 1);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			
			// 빌트인 명령어 처리
			if (is_builtin(cmd->argv[0]))
			{
				exit(execute_builtin(cmd, shell));
			}
			
			execvp(cmd->argv[0], cmd->argv);
			perror("execvp");
			_exit(1);
		}
		
		// 부모 프로세스 fd 정리
		if (prev_read != -1)
			close(prev_read);
		if (!is_last)
		{
			close(pipefd[1]);
			prev_read = pipefd[0];
		}
		
		cmd = cmd->next;
	}
	
	// 모든 자식 프로세스 대기
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				shell->last_exit_status = 130;
			else if (WTERMSIG(status) == SIGQUIT)
				shell->last_exit_status = 131;
			else
				shell->last_exit_status = 128 + WTERMSIG(status);
		}
	}
}


void handle_heredoc(t_cmd *cmd)
{
	t_redir *r;
	int pipefd[2];
	char *line;
	pid_t pid;
	int status;

	r = cmd->redir;
	while (r)
	{
		if (r->type == TK_HEREDOC)
		{
			if (pipe(pipefd) < 0)
			{
				perror("pipe");
				return;
			}
			
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				close(pipefd[0]);
				close(pipefd[1]);
				return;
			}
			
			if (pid == 0)
			{
				// 자식 프로세스: 히어독 내용을 파이프에 쓰기
				close(pipefd[0]);  // 읽기 종료 닫기
				
				while (1)
				{
					line = readline("> ");
					if (!line || !ft_strcmp(line, r->file))
					{
						if (line)
							free(line);
						break;
					}
					write(pipefd[1], line, ft_strlen(line));
					write(pipefd[1], "\n", 1);
					free(line);
				}
				
				close(pipefd[1]);
				exit(0);
			}
			else
			{
				// 부모 프로세스
				close(pipefd[1]);  // 쓰기 종료 닫기
				waitpid(pid, &status, 0);
				
				// 기존 파일 이름 해제
				free(r->file);
				
				// 간단한 임시 파일 이름 생성
				char temp_file[25];
				ft_strcpy(temp_file, "/tmp/heredoc_tmp");
				
				int fd = open(temp_file, O_RDWR | O_CREAT | O_TRUNC, 0600);
				if (fd < 0)
				{
					perror("open");
					close(pipefd[0]);
					return;
				}
				
				char buffer[4096];
				int bytes_read;
				
				while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer))) > 0)
					write(fd, buffer, bytes_read);
				
				close(pipefd[0]);
				close(fd);
				
				r->file = ft_strdup(temp_file);
				r->type = TK_REDIR_IN;
			}
		}
		r = r->next;
	}
}
