/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:07:55 by djang             #+#    #+#             */
/*   Updated: 2025/05/18 18:07:57 by djang            ###   ########.fr       */
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

// utils_tokenize.c
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
		return (0);
	}
	return (1);
}

void	process_blank(char *input, int *i, char *buf, int *buf_idx, t_token **head)
{
	while (is_blank(input[*i]))
	{
		(*i)++;
		if (*buf_idx > 0)
		{
			buf[*buf_idx] = '\0';
			add_token(head, buf, TK_WORD);
			*buf_idx = 0;
		}
	}
}

int	process_special(char *input, int i, char *buf, int *buf_idx, t_token **head)
{
	if (*buf_idx > 0)
	{
		buf[*buf_idx] = '\0';
		add_token(head, buf, TK_WORD);
		*buf_idx = 0;
	}
	return (handle_special_token(input, i, head));
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
	else
		add_token(head, temp, TK_REDIR_IN);
	return (i + 1);
}

// tokenize.c
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
		{
			if (handle_quote(input, &i, buf, &buf_idx))
			{
				printf("minishell: unexpected EOF while looking for matching quote\n");
				free_token_list(head);
				return (NULL);
			}
		}
		else
			buf[buf_idx++] = input[i++];
	}
	if (buf_idx > 0)
	{
		buf[buf_idx] = '\0';
		add_token(&head, buf, TK_WORD);
	}
	return (head);
}
