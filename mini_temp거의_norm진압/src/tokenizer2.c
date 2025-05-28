/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:13:51 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:13:52 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token_with_quote(t_token **head, char *str, t_token_type type,
		int quote_type)
{
	t_token	*new;
	t_token	*cur;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return ;
	new->str = ft_strdup(str);
	new->type = type;
	new->quote_type = quote_type;
	new->next = NULL;
	if (!*head)
		*head = new;
	else
	{
		cur = *head;
		while (cur->next)
			cur = cur->next;
		cur->next = new;
	}
}

void	process_blank(t_tokenize_data *data, int *i)
{
	while (is_blank(data->input[*i]))
		(*i)++;
	if (*(data->buf_idx) > 0)
	{
		data->buf[*(data->buf_idx)] = '\0';
		add_token(data->head, data->buf, TK_WORD);
		*(data->buf_idx) = 0;
	}
}

int	process_special(t_tokenize_data *data, int i)
{
	if (*(data->buf_idx) > 0)
	{
		data->buf[*(data->buf_idx)] = '\0';
		add_token(data->head, data->buf, TK_WORD);
		*(data->buf_idx) = 0;
	}
	return (handle_special_token(data->input, i, data->head));
}

int	handle_special_token(char *input, int i, t_token **head)
{
	char	temp[3];

	if (input[i] == '>' && input[i + 1] == '>')
	{
		add_token(head, ">>", TK_REDIR_APPEND);
		return (i + 2);
	}
	else if (input[i] == '<' && input[i + 1] == '<')
	{
		add_token(head, "<<", TK_HEREDOC);
		return (i + 2);
	}
	temp[0] = input[i];
	temp[1] = 0;
	if (input[i] == '|')
		add_token(head, temp, TK_PIPE);
	else if (input[i] == '>')
		add_token(head, temp, TK_REDIR_OUT);
	else if (input[i] == '<')
		add_token(head, temp, TK_REDIR_IN);
	return (i + 1);
}
