/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:13:21 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:13:24 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_token(t_token **head, char *str, t_token_type type)
{
	t_token	*new;
	t_token	*cur;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return ;
	new->quote_type = 0;
	new->str = ft_strdup(str);
	new->type = type;
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

void	free_token_list(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head->str);
		free(head);
		head = tmp;
	}
}

int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	handle_quote(char *input, int *i, char *buf, int *buf_idx)
{
	char	quote;
	int		quote_type;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		buf[(*buf_idx)++] = input[*i];
		(*i)++;
	}
	if (input[*i] == quote)
	{
		(*i)++;
		if (quote == '\'')
			quote_type = 1;
		else
			quote_type = 2;
		return (quote_type);
	}
	return (-1);
}
