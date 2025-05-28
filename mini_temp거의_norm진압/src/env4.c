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
