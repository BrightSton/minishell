/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 20:38:14 by djang             #+#    #+#             */
/*   Updated: 2025/05/18 20:38:16 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_cmd	*create_new_cmd(void)
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

static void	add_arg(t_cmd *cmd, char *str)
{
	int		len;
	char	**new_argv;
	int		i;

	len = 0;
	if (cmd->argv)
		while (cmd->argv[len])
			len++;
	new_argv = (char **)malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (cmd->argv && cmd->argv[i])
	{
		new_argv[i] = cmd->argv[i];
		i++;
	}
	new_argv[i++] = ft_strdup(str);
	new_argv[i] = NULL;
	free(cmd->argv);
	cmd->argv = new_argv;
}

static void	add_redir(t_cmd *cmd, int type, char *file)
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

t_cmd	*parse_tokens(t_token *token)
{
	t_cmd	*cmd_head;
	t_cmd	*cur_cmd;

	cmd_head = NULL;
	cur_cmd = NULL;
	while (token)
	{
		if (!cmd_head)
		{
			cur_cmd = create_new_cmd();
			cmd_head = cur_cmd;
		}
		else if (token->type == TK_PIPE)
		{
			cur_cmd->next = create_new_cmd();
			cur_cmd = cur_cmd->next;
			token = token->next;
			continue ;
		}
		if (token->type == TK_WORD)
			add_arg(cur_cmd, token->str);
		else if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT
			|| token->type == TK_REDIR_APPEND || token->type == TK_HEREDOC)
		{
			if (token->next && token->next->type == TK_WORD)
			{
				add_redir(cur_cmd, token->type, token->next->str);
				token = token->next;
			}
			else
			{
				printf("minishell: syntax error near unexpected token\n");
				free_cmd_list(cmd_head);
				return (NULL);
			}

		}
		token = token->next;
	}
	return (cmd_head);
}

void	free_cmd_list(t_cmd *cmd)
{
	t_cmd	*tmp;
	t_redir	*rtmp;
	int		i;

	while (cmd)
	{
		tmp = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		while (cmd->redir)
		{
			rtmp = cmd->redir->next;
			free(cmd->redir->file);
			free(cmd->redir);
			cmd->redir = rtmp;
		}
		free(cmd);
		cmd = tmp;
	}
}

void	print_cmd_list(t_cmd *cmd)
{
	int	i;
	t_redir	*r;

	while (cmd)
	{
		printf("cmd: ");
		i = 0;
		if (cmd->argv)
		{
			while (cmd->argv[i])
			{
				printf("[%s] ", cmd->argv[i]);
				i++;
			}
		}
		printf("\n");
		r = cmd->redir;
		while (r)
		{
			printf("  redir type: %d, file: %s\n", r->type, r->file);
			r = r->next;
		}
		cmd = cmd->next;
	}
}

//static int validate_redirection(t_token *token)
//{
//	if (!token)
//		return (0);

//	if (token->type == TK_REDIR_IN || token->type == TK_REDIR_OUT ||
//		token->type == TK_REDIR_APPEND || token->type == TK_HEREDOC)
//	{
//		if (!token->next || token->next->type != TK_WORD)
//			return (0);
//	}
//	return (1);
//}