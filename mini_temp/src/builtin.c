/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:13:42 by djang             #+#    #+#             */
/*   Updated: 2025/05/22 20:13:45 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || 
		!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
		!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env") ||
		!ft_strcmp(cmd, "exit"));
}

int	ft_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->size)
	{
		if (env->value[i] && env->value[i][0] != '\0')
			printf("%s=%s\n", env->key[i], env->value[i]);
		i++;
	}
	return (0);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return(0);
		i++;
	}
	return (1);
}

int	ft_export(char **args, t_env *env)
{
	int		i;
	int		status;
	char	*key;
	char	*value;
	char	*equal_sign;

	status = 0;
	if (!args[1])
	{
		i = 0;
		while (i < env->size)
		{
			printf("declare -x %s", env->key[i]);
			if (env->value[i] && env->value[i][0] != '\0')
				printf("=\"%s\"", env->value[i]);
			printf("\n");
			i++;
		}
		return (0);
	}
	i = 1;
	while (args[i])
	{
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
		{
			key = ft_substr(args[i], 0, equal_sign - args[i]);
			value = ft_strdup(equal_sign + 1);
			if (!is_valid_identifier(key))
			{
				printf("minishell: export: `%s': not a valid identifier\n", args[i]);
				status = 1;
			}
			else
				add_env(env, key, value);
			free(key);
			free(value);
		}
		else
		{
			if (!is_valid_identifier(args[i]))
			{
				printf("minishell: export: `%s': not a valid identifier\n", args[i]);
				status = 1;
			}
			else if (get_env_value(env, args[i]) == NULL)
				add_env(env, args[i],"");
		}
		i++;
	}
	return (status);
}

int	ft_unset(char **args, t_env *env)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
		return (0);
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
			status = 1;
		}
		else
			remove_env(env, args[i]);
		i++;
	}
	return (status);
}

int	ft_echo(char **args)
{
	int	i;
	int	n_option;

	n_option = 0;
	i = 1;
	if (args[1] && !ft_strcmp(args[1], "-n"))
	{
		n_option = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!n_option)
		printf("\n");
	return (0);
}

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		printf("%s\n", cwd);
		return (0);
	}
	else
	{
		perror("pwd");
		return (1);
	}
}

int	ft_cd(char **args, t_env *env)
{
	char	*path;

	if (!args[1] || !ft_strcmp(args[1], "~"))
	{
		path = get_env_value(env, "HOME");
		if (!path)
		{
			printf("minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = args[1];
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_exit(char **args, t_shell *shell)
{
	int	status;

	printf("exit\n");
	if (!args[1])
		exit(shell->last_exit_status);
	
	if (!ft_isdigit(args[1][0]) && args[1][0] != '-' && args[1][0] != '+')
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit(255);
	}

	status = ft_atoi(args[1]);

	if (args[1] && args[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	exit(status);
}

int execute_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!ft_strcmp(cmd->argv[0], "echo"))
		return (ft_echo(cmd->argv));
	else if (!ft_strcmp(cmd->argv[0], "cd"))
		return (ft_cd(cmd->argv, shell->env));
	else if (!ft_strcmp(cmd->argv[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->argv[0], "env"))
		return (ft_env(shell->env));
	else if (!ft_strcmp(cmd->argv[0], "export"))
		return (ft_export(cmd->argv, shell->env));
	else if (!ft_strcmp(cmd->argv[0], "unset"))
		return (ft_unset(cmd->argv, shell->env));
	else if (!ft_strcmp(cmd->argv[0], "exit"))
		return (ft_exit(cmd->argv, shell));
	return (1);
}
