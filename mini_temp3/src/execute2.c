/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:16:29 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:16:30 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	apply_redir(t_cmd *cmd)
{
	t_redir	*r;

	r = cmd->redir;
	while (r)
	{
		if (!r->file || !r->file[0])
		{
			printf("minishell: syntax error near unexpected token\n");
			_exit(1);
		}
		if (r->type == TK_REDIR_IN)
			handle_input_redir(r);
		else if (r->type == TK_REDIR_OUT)
			handle_output_redir(r);
		else if (r->type == TK_REDIR_APPEND)
			handle_append_redir(r);
		else if (r->type == TK_HEREDOC)
			handle_heredoc_redir(r);
		r = r->next;
	}
}

void	setup_child_process(t_cmd *cmd, int prev_read, int *pipefd,
		int is_last)
{
	set_signal_child();
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
}

void	execute_child_process(t_cmd *cmd, t_shell *shell)
{
	if (is_builtin(cmd->argv[0]))
		exit(execute_builtin(cmd, shell));
	execvp(cmd->argv[0], cmd->argv);
	perror("execvp");
	_exit(1);
}

void	handle_child_exit_status(int status, t_shell *shell)
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
