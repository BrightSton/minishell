/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:21:31 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:21:32 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_regular_char(char *str, int *i, char *result)
{
	char	temp_str[2];
	char	*old;

	temp_str[0] = str[*i];
	temp_str[1] = '\0';
	old = result;
	result = ft_strjoin(result, temp_str);
	free(old);
	(*i)++;
	return (result);
}

char	*process_dollar_expansion(char *str, int *i, char *result,
		t_env *env, int exit_status)
{
	(*i)++;
	if (str[*i] == '?')
	{
		result = handle_exit_status(result, exit_status);
		(*i)++;
	}
	else if (ft_isalnum(str[*i]) || str[*i] == '_')
		result = handle_env_var(str, i, result, env);
	else
		result = handle_dollar_char(str, i, result);
	return (result);
}

char	*expand_env_vars(char *str, t_env *env, int exit_status)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			result = process_dollar_expansion(str, &i, result, env,
					exit_status);
		else
			result = handle_regular_char(str, &i, result);
		if (!result)
			return (NULL);
	}
	return (result);
}

int	update_existing_env(t_env *env, char *key, char *value)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (ft_strcmp(env->key[i], key) == 0)
		{
			free(env->value[i]);
			env->value[i] = ft_strdup(value);
			return (0);
		}
		i++;
	}
	return (1);
}
