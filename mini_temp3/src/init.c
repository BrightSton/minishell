/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:20:01 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:20:02 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_env_vars(char **envp)
{
	int	cnt;

	cnt = 0;
	while (envp[cnt])
		cnt++;
	return (cnt);
}

t_env	*allocate_env(int cnt)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->size = cnt;
	env->key = malloc(sizeof(char *) * (cnt + 1));
	env->value = malloc(sizeof(char *) * (cnt + 1));
	if (!env->key || !env->value)
	{
		free(env->key);
		free(env->value);
		free(env);
		return (NULL);
	}
	return (env);
}

void	parse_env_var(char *envp_line, t_env *env, int i)
{
	char	*sep;
	int		key_len;

	sep = ft_strchr(envp_line, '=');
	key_len = sep - envp_line;
	env->key[i] = ft_substr(envp_line, 0, key_len);
	env->value[i] = ft_strdup(sep + 1);
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;
	int		cnt;

	cnt = count_env_vars(envp);
	env = allocate_env(cnt);
	if (!env)
		return (NULL);
	i = 0;
	while (i < cnt)
	{
		parse_env_var(envp[i], env, i);
		i++;
	}
	env->key[cnt] = NULL;
	env->value[cnt] = NULL;
	return (env);
}

void	free_env(t_env *env)
{
	int	i;

	if (!env)
		return ;
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
