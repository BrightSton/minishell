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
			exit(1);
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
	apply_redir(cmd);
}

void	execute_from_path(t_cmd *cmd, t_shell *shell, char **env_array)
{
	char	*path;

	path = find_command_in_path(cmd->argv[0], shell->env);
	if (path)
	{
		execve(path, cmd->argv, env_array);
		free(path);
	}
}

void	execute_child_process(t_cmd *cmd, t_shell *shell)
{
	int		status;
	char	**env_array;

	if (is_builtin(cmd->argv[0]))
	{
		status = execute_builtin(cmd, shell);
		free_env(shell->env);
		free_cmd_list(cmd);
		exit(status);
	}
	env_array = env_to_array(shell->env);
	if (ft_strchr(cmd->argv[0], '/'))
		check_file_and_execute(cmd, shell, env_array);
	else
		execute_from_path(cmd, shell, env_array);
	print_error("minishell: ", cmd->argv[0], ": command not found\n");
	cleanup_and_exit(shell, cmd, env_array, 127);
}

void	handle_child_exit_status(int status, t_shell *shell)
{
	int	exit_code;
	int	sig;

	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code == 141)
			shell->last_exit_status = 0;
		else
			shell->last_exit_status = exit_code;
	}
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGPIPE)
			shell->last_exit_status = 0;
		else if (sig == SIGINT)
			shell->last_exit_status = 130;
		else if (sig == SIGQUIT)
			shell->last_exit_status = 131;
		else
			shell->last_exit_status = 128 + sig;
	}
}
