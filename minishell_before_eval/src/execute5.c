/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 03:59:56 by djang             #+#    #+#             */
/*   Updated: 2025/06/02 03:59:58 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cleanup_and_exit(t_shell *shell, t_cmd *cmd, char **env_array, int code)
{
	free_env_array(env_array);
	free_env(shell->env);
	free_cmd_list(cmd);
	exit(code);
}

void	handle_directory_error(t_cmd *cmd, t_shell *shell, char **env_array)
{
	print_error("minishell: ", cmd->argv[0], ": Is a directory\n");
	cleanup_and_exit(shell, cmd, env_array, 126);
}

void	handle_permission_error(t_cmd *cmd, t_shell *shell, char **env_array)
{
	print_error("minishell: ", cmd->argv[0], ": Permission denied\n");
	cleanup_and_exit(shell, cmd, env_array, 126);
}

void	handle_file_not_found(t_cmd *cmd, t_shell *shell, char **env_array)
{
	print_error("minishell: ", cmd->argv[0], ": No such file or directory\n");
	cleanup_and_exit(shell, cmd, env_array, 127);
}

void	check_file_and_execute(t_cmd *cmd, t_shell *shell, char **env_array)
{
	struct stat	st;

	if (stat(cmd->argv[0], &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			handle_directory_error(cmd, shell, env_array);
		if (access(cmd->argv[0], X_OK) != 0)
			handle_permission_error(cmd, shell, env_array);
		execve(cmd->argv[0], cmd->argv, env_array);
	}
	else
		handle_file_not_found(cmd, shell, env_array);
}
