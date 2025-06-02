/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:25:42 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:25:43 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_export_with_value(char *arg, t_env *env)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	int		status;

	equal_sign = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, equal_sign - arg);
	value = ft_strdup(equal_sign + 1);
	status = 0;
	if (!is_valid_identifier(key))
	{
		print_error_export(arg);
		status = 1;
	}
	else
		add_env(env, key, value);
	free(key);
	free(value);
	return (status);
}

int	handle_export_without_value(char *arg, t_env *env)
{
	if (!is_valid_identifier(arg))
	{
		print_error_export(arg);
		return (1);
	}
	else if (get_env_value(env, arg) == NULL)
		add_env(env, arg, "");
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	int		i;
	int		status;
	char	*equal_sign;

	status = 0;
	if (!args[1])
	{
		print_export_vars(env);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
			status |= handle_export_with_value(args[i], env);
		else
			status |= handle_export_without_value(args[i], env);
		i++;
	}
	return (status);
}

int	ft_unset(char **args, t_env *env)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n",
				args[i]);
			status = 1;
		}
		else
			remove_env(env, args[i]);
		i++;
	}
	return (status);
}
