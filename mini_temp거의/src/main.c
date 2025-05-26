/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 22:15:16 by djang             #+#    #+#             */
/*   Updated: 2025/05/25 22:15:17 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_token_list(t_token *head)
{
	while (head)
	{
		printf("token: [%s], type: %d\n", head->str, head->type);
		head = head->next;
	}
}

void	handle_signal_status(t_shell *shell)
{
	if (g_signal_num == SIGINT)
	{
		shell->last_exit_status = 130;
		g_signal_num = 0;
	}
}

void	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_cmd	*cmds;

	tokens = tokenize(input);
	if (tokens)
		tokens = expand_tokens(tokens, shell->env, shell->last_exit_status);
	cmds = parse_tokens(tokens);
	free_token_list(tokens);
	if (cmds)
		execute_cmd(cmds, shell);
	

	free_cmd_list(cmds);
}

void	main_loop(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		handle_signal_status(shell);
		if (*input)
			add_history(input);
		process_input(input, shell);
		free(input);
	}
	free_env(shell->env);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	shell.env = init_env(envp);
	shell.last_exit_status = 0;
	set_signal();
	main_loop(&shell);
	
	return (0);
}
