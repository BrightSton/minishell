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
	new->str =ft_strdup(str);
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

t_token	*tokenize(char *input)
{
	t_token	*head;
	int		i;
	int		start;

	head = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '|')
		{
			add_token(&head, "|", TK_PIPE);
			i++;
		}
		else if (input[i] == '>' && input[i + 1] == '>')
		{
			add_token(&head, ">>", TK_REDIR_APPEND);
			i += 2;
		}
		else if (input[i] == '>')
		{
			add_token(&head, ">", TK_REDIR_OUT);
			i++;
		}
		else if (input[i] == '<' && input[i + 1] == '<')
		{
			add_token(&head, "<<", TK_HEREDOC);
			i += 2;
		}
		else if (input[i] == '<')
		{
			add_token(&head, "<", TK_REDIR_IN);
			i++;
		}
		else
		{
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '\t'
				&& input[i] != '|' && input[i] != '>' && input[i] != '<')
				i++;
			add_token(&head, ft_substr(input, start, i - start), TK_WORD);
		}
	}
	return (head);
}

//t_token	*tokenize(char *input)
//{
//	t_token	*head;
//	int		i;
//	int		start;
//	char	quote;

//	head = NULL;
//	i = 0;
//	while (input[i])
//	{
//		while (input[i] == ' ' || input[i] == '\t')
//			i++;
//		if (!input[i])
//			break ;
//		if (input[i] == '|')
//		{
//			add_token(&head, "|", TK_PIPE);
//			i++;
//		}
//		else if (input[i] == '>' && input[i + 1] == '>')
//		{
//			add_token(&head, ">>", TK_REDIR_APPEND);
//			i += 2;
//		}
//		else if (input[i] == '>')
//		{
//			add_token(&head, ">", TK_REDIR_OUT);
//			i++;
//		}
//		else if (input[i] == '<' && input[i + 1] == '<')
//		{
//			add_token(&head, "<<", TK_HEREDOC);
//			i += 2;
//		}
//		else if (input[i] == '<')
//		{
//			add_token(&head, "<", TK_REDIR_IN);
//			i++;
//		}
//		else if (input[i] == '\'' || input[i] == '"')
//		{
//			quote = input[i++];
//			start = i;
//			while (input[i] && input[i] != quote)
//				i++;
//			add_token(&head, ft_substr(input, start, i - start), TK_WORD);
//			if (input[i] == quote)
//				i++;
//		}
//		else
//		{
//			start = i;
//			while (input[i] && input[i] != ' ' && input[i] != '\t'
//				&& input[i] != '|' && input[i] != '>' && input[i] != '<'
//				&& input[i] != '\'' && input[i] != '"')
//				i++;
//			add_token(&head, ft_substr(input, start, i - start), TK_WORD);
//		}
//	}
//	return (head);
//}

//t_token	*tokenize(char *input)
//{
//	t_token	*head;
//	int		i;
//	int		start;
//	int		in_single;
//	int		in_double;

//	head = NULL;
//	i = 0;
//	start = 0;
//	in_single = 0;
//	in_double = 0;
//	while (input[i])
//	{
//		if (!in_single && !in_double && (input[i] == ' ' || input[i] == '\t'))
//		{
//			if (i > start)
//				add_token(&head, ft_substr(input, start, i - start), TK_WORD);
//			while (input[i] == ' ' || input[i] == '\t')
//				i++;
//			start = i;
//		}
//		else if (!in_single && !in_double && input[i] == '|' )
//		{
//			if (i > start)
//				add_token(&head, ft_substr(input, start, i - start), TK_WORD);
//			add_token(&head, "|", TK_PIPE);
//			i++;
//			start = i;
//		}
//		else if (!in_single && !in_double && input[i] == '>' && input[i+1] == '>')
//		{
//			if (i > start)
//				add_token(&head, ft_substr(input, start, i - start), TK_WORD);
//			add_token(&head, ">>", TK_REDIR_APPEND);
//			i += 2;
//			start = i;
//		}
//		else if (!in_single && !in_double && input[i] == '>')
//		{
//			if (i > start)
//				add_token(&head, ft_substr(input, start, i - start), TK_WORD);
//			add_token(&head, ">", TK_REDIR_OUT);
//			i++;
//			start = i;
//		}
//		else if (!in_single && !in_double && input[i] == '<' && input[i+1] == '<')
//		{
//			if (i > start)
//				add_token(&head, ft_substr(input, start, i - start), TK_WORD);
//			add_token(&head, "<<", TK_HEREDOC);
//			i += 2;
//			start = i;
//		}
//		else if (!in_single && !in_double && input[i] == '<')
//		{
//			if (i > start)
//				add_token(&head, ft_substr(input, start, i - start), TK_WORD);
//			add_token(&head, "<", TK_REDIR_IN);
//			i++;
//			start = i;
//		}
//		else if (input[i] == '\'' && !in_double)
//		{
//			in_single = !in_single;
//			i++;
//		}
//		else if (input[i] == '"' && !in_single)
//		{
//			in_double = !in_double;
//			i++;
//		}
//		else
//			i++;
//	}
//	if (i > start)
//		add_token(&head, ft_substr(input, start, i - start), TK_WORD);
//	if (in_single || in_double)
//	{
//		printf("minishell: unexpected EOF while looking for matching quote\n");
//		return (NULL);
//	}
//	return (head);
//}