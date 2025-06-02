/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 04:05:26 by djang             #+#    #+#             */
/*   Updated: 2025/06/02 04:05:28 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_paths_array(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*build_full_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}
