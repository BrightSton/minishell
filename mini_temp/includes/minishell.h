/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:37:28 by djang             #+#    #+#             */
/*   Updated: 2025/05/18 00:37:30 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//includes/minishell.h
#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include <fcntl.h>

extern volatile sig_atomic_t g_signal_num;

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APPEND,
	TK_HEREDOC
}	t_token_type;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char		**argv;
	t_redir		*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char	**key;
	char	**value;
	int		size;
}	t_env;

typedef struct s_shell
{
	t_env	*env;
	int		last_exit_status;
}	t_shell;

t_env	*init_env(char **envp);
void	free_env(t_env *env);
void	set_signal(void);

t_token	*tokenize(char *input);
void	add_token(t_token **head, char *str, t_token_type type);
void	free_token_list(t_token *head);

t_cmd	*parse_tokens(t_token *token);
void	free_cmd_list(t_cmd *cmd);
//void	print_cmd_list(t_cmd *cmd);

void	execute_cmd(t_cmd *cmd);
#endif