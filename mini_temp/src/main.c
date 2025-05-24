/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 01:04:38 by djang             #+#    #+#             */
/*   Updated: 2025/05/18 01:04:39 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

void	print_token_list(t_token *head)
{
	while (head)
	{
		printf("token: [%s], type: %d\n", head->str, head->type);
		head = head->next;
	}
}

//int	main(int argc, char **argv, char **envp)
//{
	
//	t_shell	shell;
//	char	*input;
//	t_token	*tokens;
//	t_cmd	*cmds;

//	(void)argc;
//	(void)argv;
//	shell.env = init_env(envp);
//	shell.last_exit_status = 0;
//	set_signal();

//	while (1)
//	{
//		input = readline("minishell$ ");
//		if (!input)
//		{
//			printf("exit\n");
//			break;
//		}
//		if (*input)
//			add_history(input);

//		tokens = tokenize(input);
//		if (tokens)
//			tokens = expand_tokens(tokens, shell.env, shell.last_exit_status);
//		cmds = parse_tokens(tokens);
//		//print_cmd_list(cmds);
//		//print_token_list(tokens);
//		if (cmds)
//			execute_cmd(cmds, &shell);  // 함수 시그니처 변경
//		free_cmd_list(cmds);
//		free_token_list(tokens);
//		free(input);
//	}
//	free_env(shell.env);
//	return 0;
//}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*input;
	t_token	*tokens;
	t_cmd	*cmds;

	(void)argc;
	(void)argv;
	shell.env = init_env(envp);
	shell.last_exit_status = 0;
	set_signal();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break;
		}
		if (g_signal_num == SIGINT)
		{
			shell.last_exit_status = 130;
			g_signal_num = 0;
		}
		if (*input)
			add_history(input);
		tokens = tokenize(input);
		if (tokens)
			tokens = expand_tokens(tokens, shell.env, shell.last_exit_status);
		cmds = parse_tokens(tokens);
		if (cmds)
			execute_cmd(cmds, &shell);
		
		free_cmd_list(cmds);
		free_token_list(tokens);
		free(input);
	}
	free_env(shell.env);
	return (0);
}
