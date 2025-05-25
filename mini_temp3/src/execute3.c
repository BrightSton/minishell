/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:16:55 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:16:57 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_builtin_only(t_cmd *cmd, t_shell *shell, int is_last,
		int prev_read)
{
	if (is_last && prev_read == -1 && !cmd->redir && is_builtin(cmd->argv[0]))
	{
		shell->last_exit_status = execute_builtin(cmd, shell);
		return (1);
	}
	return (0);
}

void	setup_pipe_and_fork(t_cmd *cmd, int *pipefd, int is_last,
		pid_t *pid)
{
	(void)cmd;
	if (!is_last)
	{
		if (pipe(pipefd) < 0)
		{
			perror("pipe");
			return ;
		}
	}
	*pid = fork();
	if (*pid < 0)
	{
		perror("fork");
		return ;
	}
}

void	process_single_cmd(t_cmd *cmd, t_shell *shell, int *prev_read)
{
	int		pipefd[2];
	pid_t	pid;
	int		is_last;

	is_last = (cmd->next == NULL);
	if (!cmd->argv || !cmd->argv[0])
		return ;
	if (handle_builtin_only(cmd, shell, is_last, *prev_read))
		return ;
	setup_pipe_and_fork(cmd, pipefd, is_last, &pid);
	if (pid == 0)
	{
		setup_child_process(cmd, *prev_read, pipefd, is_last);
		execute_child_process(cmd, shell);
	}
	if (*prev_read != -1)
		close(*prev_read);
	if (!is_last)
	{
		close(pipefd[1]);
		*prev_read = pipefd[0];
	}
}

void	execute_cmd(t_cmd *cmd, t_shell *shell)
{
	t_cmd	*current;
	int		prev_read;
	int		status;

	current = cmd;
	while (current)
	{
		handle_heredoc(current);
		current = current->next;
	}
	prev_read = -1;
	while (cmd)
	{
		process_single_cmd(cmd, shell, &prev_read);
		cmd = cmd->next;
	}
	while (wait(&status) > 0)
		handle_child_exit_status(status, shell);
}
