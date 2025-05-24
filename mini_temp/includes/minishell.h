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

//typedef struct s_token
//{
//	char			*str;
//	t_token_type	type;
//	struct s_token	*next;
//}	t_token;

typedef struct s_token
{
	char			*str;
	t_token_type	type;
	int				quote_type; // 0: 따옴표 없음, 1: 작은따옴표, 2: 큰따옴표
	struct s_token	*next;
} t_token;


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
int	handle_special_token(char *input, int i, t_token **head);
int	process_special(char *input, int i, char *buf, int *buf_idx, t_token **head);
void	process_blank(char *input, int *i, char *buf, int *buf_idx, t_token **head);
int	handle_quote(char *input, int *i, char *buf, int *buf_idx);
int	is_special(char c);
int	is_blank(char c);


void	add_token(t_token **head, char *str, t_token_type type);
void	free_token_list(t_token *head);

t_cmd	*parse_tokens(t_token *token);
void	free_cmd_list(t_cmd *cmd);
//void	print_cmd_list(t_cmd *cmd);

void	execute_cmd(t_cmd *cmd, t_shell *shell);


// 환경변수 관련 함수
char	*get_env_value(t_env *env, char *key);
char	*expand_env_vars(char *str, t_env *env, int exit_status);
t_token	*expand_tokens(t_token *tokens, t_env *env, int exit_status);

// 환경변수 관련 함수
int add_env(t_env *env, char *key, char *value);
int remove_env(t_env *env, char *key);

// 빌트인 명령어 관련 함수
int is_builtin(char *cmd);
int ft_echo(char **args);
int ft_cd(char **args, t_env *env);
int ft_pwd(void);
int ft_env(t_env *env);
int ft_export(char **args, t_env *env);
int ft_unset(char **args, t_env *env);
int ft_exit(char **args, t_shell *shell);
int execute_builtin(t_cmd *cmd, t_shell *shell);


// 시그널 관련 함수
void	set_signal_child(void);
void	set_signal_heredoc(void);
void	sigquit_handler(int signo);

////
void handle_heredoc(t_cmd *cmd);


//
void add_token_with_quote(t_token **head, char *str, t_token_type type, int quote_type);

#endif