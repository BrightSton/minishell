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

static int	get_num_start_index(char *str)
{
	if (str[0] == '+' || str[0] == '-')
		return (1);
	return (0);
}

static int	is_overflow_range(char *num_part, int is_negative)
{
	if (ft_strlen(num_part) > 19)
		return (1);
	if (ft_strlen(num_part) == 19)
	{
		if (is_negative && ft_strcmp(num_part, "9223372036854775808") > 0)
			return (1);
		if (!is_negative && ft_strcmp(num_part, "9223372036854775807") > 0)
			return (1);
	}
	return (0);
}

int	is_valid_exit_number(char *str)
{
	int		i;
	char	*num_part;
	int		start_idx;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	start_idx = get_num_start_index(str);
	num_part = str + start_idx;
	if (is_overflow_range(num_part, str[0] == '-'))
		return (0);
	return (1);
}

int	ft_exit(char **args, t_shell *shell, t_cmd *cmd)
{
	int	status;

	printf("exit\n");
	if (!args[1])
	{
		free_env(shell->env);
		free_cmd_list(cmd);
		exit(shell->last_exit_status);
	}
	if (!is_valid_exit_number(args[1]))
	{
		print_error_exit_numeric(args[1]);
		free_env(shell->env);
		free_cmd_list(cmd);
		exit(2);
	}
	if (args[1] && args[2])
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	status = ft_atoi(args[1]);
	free_env(shell->env);
	free_cmd_list(cmd);
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
		return (ft_exit(cmd->argv, shell, cmd));
	return (1);
}
