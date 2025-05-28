/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:03:43 by djang             #+#    #+#             */
/*   Updated: 2025/05/28 16:03:44 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*tokenize(char *input)
{
	t_tokenize_data	data;
	char			buf[4096];
	int				buf_idx;
	int				i;

	data.input = input;
	data.buf = buf;
	data.buf_idx = &buf_idx;
	data.head = &(t_token *){NULL};
	buf_idx = 0;
	i = 0;
	while (input[i])
	{
		i = process_char(&data, i);
		if (i == -1)
			return (NULL);
	}
	finalize_tokenize(buf, *(data.buf_idx), data.head);
	return (*(data.head));
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
