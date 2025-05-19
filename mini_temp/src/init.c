/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 01:04:20 by djang             #+#    #+#             */
/*   Updated: 2025/05/18 01:04:21 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;
	int		cnt;
	char	*sep;
	int		key_len;

	i = 0;
	cnt = 0;
	while (envp[cnt])
		cnt++;
	env = (t_env *) malloc(sizeof(t_env));
	env->size = cnt;
	env->key = malloc(sizeof(char *) * (cnt+1));
	env->value = malloc(sizeof(char *) * (cnt+1));
	while(i < cnt)
	{
		sep = ft_strchr(envp[i], '=');
		key_len = sep - envp[i];
		env->key[i] = ft_substr(envp[i], 0, key_len);
		env->value[i] = ft_strdup(sep + 1);
		i++;
	}
	env->key[cnt] = NULL;
	env->value[cnt] = NULL;
	return env;
}
void	free_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		free(env->key[i]);
		free(env->value[i]);
		i++;
	}
	free(env->key);
	free(env->value);
	free(env);	
}


