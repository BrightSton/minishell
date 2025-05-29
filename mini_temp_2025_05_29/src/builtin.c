/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:25:18 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:25:19 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (env->value[i] && env->value[i][0] != '\0')
			printf("%s=%s\n", env->key[i], env->value[i]);
		i++;
	}
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_export_vars(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		printf("declare -x %s", env->key[i]);
		if (env->value[i] && env->value[i][0] != '\0')
			printf("=\"%s\"", env->value[i]);
		printf("\n");
		i++;
	}
}
