/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:19:06 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:19:08 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*handle_pipe_token(t_cmd *cmd_head, t_cmd **cur_cmd)
{
	if (!(*cur_cmd)->next)
	{
		(*cur_cmd)->next = create_new_cmd();
		if (!(*cur_cmd)->next)
		{
			free_cmd_list(cmd_head);
			return (NULL);
		}
	}
	*cur_cmd = (*cur_cmd)->next;
	return (cmd_head);
}

t_cmd	*handle_redir_token(t_token *token, t_cmd *cmd_head,
		t_cmd *cur_cmd)
{
	if (!token->next || token->next->type != TK_WORD)
	{
		printf("minishell: syntax error\n");
		free_cmd_list(cmd_head);
		return (NULL);
	}
	add_redir(cur_cmd, token->type, token->next->str);
	return (cmd_head);
}

t_token	*process_token(t_token *token, t_cmd **cmd_head,
		t_cmd **cur_cmd)
{
	if (!*cmd_head)
	{
		*cur_cmd = create_new_cmd();
		if (!*cur_cmd)
			return (NULL);
		*cmd_head = *cur_cmd;
	}
	else if (token->type == TK_PIPE)
	{
		*cmd_head = handle_pipe_token(*cmd_head, cur_cmd);
		if (!*cmd_head)
			return (NULL);
		return (token->next);
	}
	if (token->type == TK_WORD)
		add_arg(*cur_cmd, token->str);
	else if (token->type >= TK_REDIR_IN && token->type <= TK_HEREDOC)
	{
		*cmd_head = handle_redir_token(token, *cmd_head, *cur_cmd);
		if (!*cmd_head)
			return (NULL);
		token = token->next;
	}
	return (token->next);
}

t_cmd	*parse_tokens(t_token *token)
{
	t_cmd	*cmd_head;
	t_cmd	*cur_cmd;

	cmd_head = NULL;
	cur_cmd = NULL;
	while (token)
	{
		token = process_token(token, &cmd_head, &cur_cmd);
		if (!token && !cmd_head)
			return (NULL);
	}
	return (cmd_head);
}
