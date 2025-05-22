/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:54:51 by djang             #+#    #+#             */
/*   Updated: 2025/05/22 00:54:52 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

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

char	*expand_env_vars(char *str, t_env *env, int exit_status)
{
	int		i;
	int		j;
	char	*result;
	char	*var_name;
	char	*var_value;
	char	*temp;
	char	*old;
	char	temp_str[3];

	result = ft_strdup("");
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i+1])
		{
			i++;
			if (str[i] == '?')
			{
				temp = ft_itoa(exit_status);
				old = result;
				result = ft_strjoin(result, temp);
				free(old);
				free(temp);
				i++;
			}
			else if (ft_isalnum(str[i]) || str[i] == '_')
			{
				j = i;
				while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
					j++;
				var_name = ft_substr(str, i , j - i);
				var_value = get_env_value (env, var_name);
				if (var_value)
				{
					old = result;
					result = ft_strjoin(result, var_value);
					free(old);
				}
				free(var_name);
				i = j;
			}
			else
			{
				temp_str[0] = '$';
				temp_str[1] = str[i];
				temp_str[2] = '\0';
				old = result;
				result = ft_strjoin(result, temp_str);
				free(old);
				i++;
			}
		}
		else
		{
			temp_str[0] = str[i];
			temp_str[1] = '\0';
			old = result;
			result = ft_strjoin(result, temp_str);
			free(old);
			i++;
		}
	}
	return (result);
}

int	add_env(t_env *env, char *key, char *value)
{
	int		i;
	char	**new_key;
	char	**new_value;

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
	new_key = malloc(sizeof(char *) * (env->size + 2));
	new_value = malloc(sizeof(char *) * (env->size + 2));
	if (!new_key || !new_value)
		return (1);
	i = 0;
	while (i < env->size)
	{
		new_key[i] = env->key[i];
		new_value[i] = env->value[i];
		i++;
	}
	new_key[i] = ft_strdup(key);
	new_value[i] = ft_strdup(value);
	new_key[i + 1] = NULL;
	new_value[i + 1] = NULL;
	free(env->key);
	free(env->value);
	env->key = new_key;
	env->value =new_value;
	env->size++;
	return (0);
}

int remove_env(t_env *env, char *key)
{
	int i;
	int j;
	char **new_key;
	char **new_value;

	i = 0;
	while (i < env->size && ft_strcmp(env->key[i], key) != 0)
		i++;
	if (i == env->size)
		return (0);
	new_key = malloc(sizeof(char *) * env->size);
	new_value = malloc(sizeof(char *) * env->size);
	if (!new_key || !new_value)
		return (1);
	j = 0;
	i = -1;
	while (++i < env->size)
	{
		if (ft_strcmp(env->key[i], key) != 0)
		{
			new_key[j] = env->key[i];
			new_value[j] = env->value[i];
			j++;
		}
		else
		{
			free(env->key[i]);
			free(env->value[i]);
		}
	}
	new_key[j] = NULL;
	new_value[j] = NULL;
	free(env->key);
	free(env->value);
	env->key = new_key;
	env->value = new_value;
	env->size--;
	return (0);
}

