/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:26:30 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:26:31 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(char **args, t_shell *shell)
{
	int	status;

	printf("exit\n");
	if (!args[1])
		exit(shell->last_exit_status);
	handle_exit_error(args);
	status = ft_atoi(args[1]);
	if (args[1] && args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit(status);
}

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (ft_echo(cmd->argv));
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (ft_cd(cmd->argv, shell->env));
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (ft_env(shell->env));
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (ft_export(cmd->argv, shell->env));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (ft_unset(cmd->argv, shell->env));
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (ft_exit(cmd->argv, shell));
	return (1);
}
