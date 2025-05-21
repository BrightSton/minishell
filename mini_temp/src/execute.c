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



void	execute_cmd(t_cmd *cmd, t_shell *shell)
{
	int		pipefd[2];
	int		prev_read;
	pid_t	pid;
	int		is_last;
	int		status;

	prev_read = -1;
	while (cmd)
	{
		is_last = (cmd->next == NULL);
		if (!cmd->argv || !cmd->argv[0])
		{
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
			apply_redir(cmd);
			if (prev_read != -1)
			{
				dup2(prev_read, 0);
				close(prev_read);
			}
			if (!is_last)
			{
				dup2(pipefd[1], 1);
				close(pipefd[0]);
				close(pipefd[1]);
			}
			execvp(cmd->argv[0], cmd->argv);
			perror("execvp");
			_exit(1);
		}
		if (prev_read != -1)
			close(prev_read);
		if (!is_last)
		{
			close(pipefd[1]);
			prev_read = pipefd[0];
		}
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
			shell->last_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->last_exit_status = 128 + WTERMSIG(status);
	}
}
