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

void	handle_quote_in_tokenize(t_tokenize_data *data, int *i)
{
	int	quote_type;

	quote_type = handle_quote(data->input, i, data->buf, data->buf_idx);
	if (quote_type == -1)
	{
		printf("minishell: unexpected EOF while looking for matching quote\n");
		free_token_list(*(data->head));
		*(data->head) = NULL;
		return ;
	}
	if (!is_blank(data->input[*i]) && !is_special(data->input[*i])
		&& data->input[*i] != '\0' && data->input[*i] != '\''
		&& data->input[*i] != '"')
		return ;
	if (*(data->buf_idx) > 0)
	{
		data->buf[*(data->buf_idx)] = '\0';
		add_token_with_quote(data->head, data->buf, TK_WORD, quote_type);
		*(data->buf_idx) = 0;
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

int	process_quote_char(t_tokenize_data *data, int *i)
{
	handle_quote_in_tokenize(data, i);
	if (!*(data->head) && (data->input[*i - 1] == '\''
			|| data->input[*i - 1] == '"'))
		return (0);
	return (1);
}

int	process_regular_char(t_tokenize_data *data, int *i)
{
	data->buf[*(data->buf_idx)] = data->input[*i];
	(*(data->buf_idx))++;
	(*i)++;
	if (!*(data->head) && (data->input[*i - 1] == '\''
			|| data->input[*i - 1] == '"'))
		return (0);
	return (1);
}

int	process_char(t_tokenize_data *data, int i)
{
	if (is_blank(data->input[i]))
	{
		process_blank(data, &i);
		return (i);
	}
	else if (is_special(data->input[i]))
		return (process_special(data, i));
	else if (data->input[i] == '\'' || data->input[i] == '"')
	{
		handle_quote_in_tokenize(data, &i);
		if (!*(data->head))
			return (-1);
		return (i);
	}
	else
	{
		data->buf[*(data->buf_idx)] = data->input[i];
		(*(data->buf_idx))++;
		return (i + 1);
	}
}
