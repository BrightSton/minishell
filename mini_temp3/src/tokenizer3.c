/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:14:34 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:14:35 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_quote_in_tokenize(char *input, int *i, char *buf,
		int *buf_idx, t_token **head)
{
	int	quote_type;

	quote_type = handle_quote(input, i, buf, buf_idx);
	if (quote_type == -1)
	{
		printf("minishell: unexpected EOF while looking for matching quote\n");
		free_token_list(*head);
		*head = NULL;
		return ;
	}
	if (*buf_idx > 0)
	{
		buf[*buf_idx] = '\0';
		add_token_with_quote(head, buf, TK_WORD, quote_type);
		*buf_idx = 0;
	}
}

void	finalize_tokenize(char *buf, int buf_idx, t_token **head)
{
	if (buf_idx > 0)
	{
		buf[buf_idx] = '\0';
		add_token_with_quote(head, buf, TK_WORD, 0);
	}
}

t_token	*tokenize(char *input)
{
	t_token	*head;
	char	buf[4096];
	int		buf_idx;
	int		i;

	head = NULL;
	buf_idx = 0;
	i = 0;
	while (input[i])
	{
		if (is_blank(input[i]))
			process_blank(input, &i, buf, &buf_idx, &head);
		else if (is_special(input[i]))
			i = process_special(input, i, buf, &buf_idx, &head);
		else if (input[i] == '\'' || input[i] == '"')
			handle_quote_in_tokenize(input, &i, buf, &buf_idx, &head);
		else
			buf[buf_idx++] = input[i++];
		if (!head && (input[i - 1] == '\'' || input[i - 1] == '"'))
			return (NULL);
	}
	finalize_tokenize(buf, buf_idx, &head);
	return (head);
}

t_token	*expand_tokens(t_token *tokens, t_env *env, int exit_status)
{
	t_token	*current;
	char	*expanded;

	current = tokens;
	while (current)
	{
		if (current->type == TK_WORD && current->quote_type != 1)
		{
			expanded = expand_env_vars(current->str, env, exit_status);
			free(current->str);
			current->str = expanded;
		}
		current = current->next;
	}
	return (tokens);
}
