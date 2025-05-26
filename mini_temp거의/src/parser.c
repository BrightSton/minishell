/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:18:35 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:18:36 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*create_new_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redir = NULL;
	cmd->next = NULL;
	return (cmd);
}

char	**create_new_argv(char **old_argv, int len)
{
	char	**new_argv;
	int		i;

	new_argv = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_argv)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_argv[i] = old_argv[i];
		i++;
	}
	return (new_argv);
}

void	add_arg(t_cmd *cmd, char *str)
{
	int		len;
	char	**new_argv;

	len = 0;
	if (cmd->argv)
		while (cmd->argv[len])
			len++;
	new_argv = create_new_argv(cmd->argv, len);
	if (!new_argv)
	{
		free(cmd->argv);
		cmd->argv = NULL;
		return ;
	}
	new_argv[len] = ft_strdup(str);
	if (!new_argv[len])
	{
		free(new_argv);
		return ;
	}
	new_argv[len + 1] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

void	add_redir(t_cmd *cmd, int type, char *file)
{
	t_redir	*new;
	t_redir	*cur;

	new = (t_redir *)malloc(sizeof(t_redir));
	if (!new)
		return ;
	new->type = type;
	new->file = ft_strdup(file);
	new->next = NULL;
	if (!cmd->redir)
		cmd->redir = new;
	else
	{
		cur = cmd->redir;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

