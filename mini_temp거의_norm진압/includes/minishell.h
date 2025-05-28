/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 00:37:28 by djang             #+#    #+#             */
/*   Updated: 2025/05/18 00:37:30 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

extern volatile sig_atomic_t	g_signal_num;

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
	int				quote_type;
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
	char			**argv;
	t_redir			*redir;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			**key;
	char			**value;
	int				size;
}	t_env;

typedef struct s_tokenize_data
{
	char		*input;
	char		*buf;
	int			*buf_idx;
	t_token		**head;
}	t_tokenize_data;

typedef struct s_expand_data
{
	char	*str;
	char	*result;
	t_env	*env;
	int		exit_status;
}	t_expand_data;

typedef struct s_shell
{
	t_env			*env;
	int				last_exit_status;
}	t_shell;

/* init.c */
t_env		*init_env(char **envp);
void		free_env(t_env *env);
int			count_env_vars(char **envp);
t_env		*allocate_env(int cnt);
void		parse_env_var(char *envp_line, t_env *env, int i);

/* signal.c */
void		set_signal(void);
void		set_signal_child(void);
void		set_signal_heredoc(void);
void		sigint_handler(int signo);
void		sigquit_handler(int signo);

/* tokenizer.c */
t_token		*tokenize(char *input);
void		add_token(t_token **head, char *str, t_token_type type);
void		free_token_list(t_token *head);
int			is_blank(char c);
int			is_special(char c);
int			handle_quote(char *input, int *i, char *buf, int *buf_idx);
void		add_token_with_quote(t_token **head, char *str,
				t_token_type type, int quote_type);
void		process_blank(t_tokenize_data *data, int *i);
int			process_special(t_tokenize_data *data, int i);
int			handle_special_token(char *input, int i, t_token **head);
void		handle_quote_in_tokenize(t_tokenize_data *data, int *i);
void		finalize_tokenize(char *buf, int buf_idx, t_token **head);
int			process_quote_char(t_tokenize_data *data, int *i);
int			process_regular_char(t_tokenize_data *data, int *i);
t_token		*expand_tokens(t_token *tokens, t_env *env, int exit_status);

/* parser.c */
t_cmd		*parse_tokens(t_token *token);
void		free_cmd_list(t_cmd *cmd);
void		print_cmd_list(t_cmd *cmd);
t_cmd		*create_new_cmd(void);
char		**create_new_argv(char **old_argv, int len);
void		add_arg(t_cmd *cmd, char *str);
void		add_redir(t_cmd *cmd, int type, char *file);
t_cmd		*handle_pipe_token(t_cmd *cmd_head, t_cmd **cur_cmd);
t_cmd		*handle_redir_token(t_token *token, t_cmd *cmd_head,
				t_cmd *cur_cmd);
t_token		*process_token(t_token *token, t_cmd **cmd_head,
				t_cmd **cur_cmd);

/* execute.c */
void		execute_cmd(t_cmd *cmd, t_shell *shell);
void		handle_heredoc(t_cmd *cmd);
void		handle_input_redir(t_redir *r);
void		handle_output_redir(t_redir *r);
void		handle_append_redir(t_redir *r);
void		handle_heredoc_redir(t_redir *r);
void		apply_redir(t_cmd *cmd);
void		setup_child_process(t_cmd *cmd, int prev_read, int *pipefd,
				int is_last);
void		execute_child_process(t_cmd *cmd, t_shell *shell);
void		handle_child_exit_status(int status, t_shell *shell);
int			handle_builtin_only(t_cmd *cmd, t_shell *shell, int is_last,
				int prev_read);
void		setup_pipe_and_fork(t_cmd *cmd, int *pipefd, int is_last,
				pid_t *pid);
void		process_single_cmd(t_cmd *cmd, t_shell *shell, int *prev_read);
void		write_heredoc_content(int write_fd, char *delimiter);
void		create_temp_file(int read_fd, char **file_path);
void		process_heredoc_redir(t_redir *r);

/* env.c */
char		*get_env_value(t_env *env, char *key);
char		*expand_env_vars(char *str, t_env *env, int exit_status);
int			add_env(t_env *env, char *key, char *value);
int			remove_env(t_env *env, char *key);
char		*handle_exit_status(char *result, int exit_status);
char		*handle_env_var(char *str, int *i, char *result, t_env *env);
char		*handle_dollar_char(char *str, int *i, char *result);
char		*handle_regular_char(char *str, int *i, char *result);
char		*process_dollar_expansion(t_expand_data *data, int *i);
int			update_existing_env(t_env *env, char *key, char *value);
int			create_new_env_arrays(t_env *env, char ***new_key,
				char ***new_value);
void		copy_env_arrays(t_env *env, char **new_key, char **new_value);
int			find_env_index(t_env *env, char *key);
void		copy_env_except_index(t_env *env, char **new_key,
				char **new_value, int skip_index);

/* builtin.c */
int			is_builtin(char *cmd);
int			ft_echo(char **args);
int			ft_cd(char **args, t_env *env);
int			ft_pwd(void);
int			ft_env(t_env *env);
int			ft_export(char **args, t_env *env);
int			ft_unset(char **args, t_env *env);
int			ft_exit(char **args, t_shell *shell);
int			execute_builtin(t_cmd *cmd, t_shell *shell);
int			is_valid_identifier(char *str);
void		print_export_vars(t_env *env);
int			handle_export_with_value(char *arg, t_env *env);
int			handle_export_without_value(char *arg, t_env *env);
void		handle_exit_error(char **args);

/* main.c */
void		print_token_list(t_token *head);
void		handle_signal_status(t_shell *shell);
void		process_input(char *input, t_shell *shell);
void		main_loop(t_shell *shell);


//

int			process_char(t_tokenize_data *data, int i);
#endif
