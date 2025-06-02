/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:23:59 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:24:01 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	copy_env_except_index(t_env *env, char **new_key,
		char **new_value, int skip_index)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < env->size)
	{
		if (i != skip_index)
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
		i++;
	}
	new_key[j] = NULL;
	new_value[j] = NULL;
}

int	remove_env(t_env *env, char *key)
{
	int		index;
	char	**new_key;
	char	**new_value;

	index = find_env_index(env, key);
	if (index == -1)
		return (0);
	new_key = malloc(sizeof(char *) * env->size);
	new_value = malloc(sizeof(char *) * env->size);
	if (!new_key || !new_value)
		return (1);
	copy_env_except_index(env, new_key, new_value, index);
	free(env->key);
	free(env->value);
	env->key = new_key;
	env->value = new_value;
	env->size--;
	return (0);
}

char	**env_to_array(t_env *env)
{
	char	**env_array;
	char	*temp;
	int		i;

	env_array = malloc(sizeof(char *) * (env->size + 1));
	if (!env_array)
		return (NULL);
	i = 0;
	while (i < env->size)
	{
		temp = ft_strjoin(env->key[i], "=");
		env_array[i] = ft_strjoin(temp, env->value[i]);
		free(temp);
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

char	*find_command_in_path(char *cmd, t_env *env)
{
	char	*path_env;
	char	**paths;
	char	*full_path;
	int		i;

	path_env = get_env_value(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = build_full_path(paths[i], cmd);
		if (full_path && access(full_path, X_OK) == 0)
		{
			free_paths_array(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_paths_array(paths);
	return (NULL);
}
