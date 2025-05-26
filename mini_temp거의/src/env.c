/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:20:24 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:20:25 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (ft_strcmp(env->key[i], key) == 0)
			return (env->value[i]);
		i++;
	}
	return (NULL);
}

char	*handle_exit_status(char *result, int exit_status)
{
	char	*temp;
	char	*old;

	temp = ft_itoa(exit_status);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	old = result;
	result = ft_strjoin(result, temp);
	free(old);
	free(temp);
	return (result);
}

char	*handle_env_var(char *str, int *i, char *result, t_env *env)
{
	int		j;
	char	*var_name;
	char	*var_value;
	char	*old;

	j = *i;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	var_name = ft_substr(str, *i, j - *i);
	if (!var_name)
	{
		free(result);
		return (NULL);
	}
	var_value = get_env_value(env, var_name);
	old = result;
	result = ft_strjoin(result, var_value ? var_value : "");
	free(old);
	free(var_name);
	*i = j;
	return (result);
}

char	*handle_dollar_char(char *str, int *i, char *result)
{
	char	temp_str[3];
	char	*old;

	temp_str[0] = '$';
	temp_str[1] = str[*i];
	temp_str[2] = '\0';
	old = result;
	result = ft_strjoin(result, temp_str);
	free(old);
	(*i)++;
	return (result);
}
