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

char	*process_dollar_expansion(t_expand_data *data, int *i)
{
	(*i)++;
	if (data->str[*i] == '?')
	{
		data->result = handle_exit_status(data->result, data->exit_status);
		(*i)++;
	}
	else if (ft_isalnum(data->str[*i]) || data->str[*i] == '_')
		data->result = handle_env_var(data->str, i, data->result, data->env);
	else
		data->result = handle_dollar_char(data->str, i, data->result);
	return (data->result);
}

char	*expand_env_vars(char *str, t_env *env, int exit_status)
{
	t_expand_data	data;
	int				i;

	i = 0;
	data.str = str;
	data.env = env;
	data.exit_status = exit_status;
	data.result = ft_strdup("");
	if (!data.result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			data.result = process_dollar_expansion(&data, &i);
		else
			data.result = handle_regular_char(str, &i, data.result);
		if (!data.result)
			return (NULL);
	}
	return (data.result);
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
