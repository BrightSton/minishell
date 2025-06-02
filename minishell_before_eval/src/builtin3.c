/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:26:02 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:26:03 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_n_option(char *arg)
{
	int	i;

	if (!arg || arg[0] != '-' || arg[1] != 'n')
		return (0);
	i = 2;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_option;

	n_option = 0;
	i = 1;
	while (args[i] && is_valid_n_option(args[i]))
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	ft_cd(char **args, t_env *env)
{
	char	*path;

	if (args[1] && args[2])
	{
		print_error_cd();
		return (1);
	}
	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		path = get_env_value(env, "HOME");
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

void	handle_exit_error(char **args, t_shell *shell, t_cmd *cmd)
{
	if (!is_valid_exit_number(args[1]))
	{
		print_error_exit_numeric(args[1]);
		free_env(shell->env);
		free_cmd_list(cmd);
		exit(2);
	}
}
