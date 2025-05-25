/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:21:54 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:21:56 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	create_new_env_arrays(t_env *env, char ***new_key,
		char ***new_value)
{
	*new_key = malloc(sizeof(char *) * (env->size + 2));
	*new_value = malloc(sizeof(char *) * (env->size + 2));
	if (!*new_key || !*new_value)
		return (1);
	return (0);
}

void	copy_env_arrays(t_env *env, char **new_key, char **new_value)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		new_key[i] = env->key[i];
		new_value[i] = env->value[i];
		i++;
	}
}

int	add_env(t_env *env, char *key, char *value)
{
	char	**new_key;
	char	**new_value;

	if (update_existing_env(env, key, value) == 0)
		return (0);
	if (create_new_env_arrays(env, &new_key, &new_value))
		return (1);
	copy_env_arrays(env, new_key, new_value);
	new_key[env->size] = ft_strdup(key);
	new_value[env->size] = ft_strdup(value);
	new_key[env->size + 1] = NULL;
	new_value[env->size + 1] = NULL;
	free(env->key);
	free(env->value);
	env->key = new_key;
	env->value = new_value;
	env->size++;
	return (0);
}

int	find_env_index(t_env *env, char *key)
{
	int	i;

	i = 0;
	while (i < env->size && ft_strcmp(env->key[i], key) != 0)
		i++;
	if (i == env->size)
		return (-1);
	return (i);
}
