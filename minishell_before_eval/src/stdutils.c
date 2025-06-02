/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stdutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 00:05:22 by djang             #+#    #+#             */
/*   Updated: 2025/05/30 00:05:24 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_error(char *prefix, char *arg, char *suffix)
{
	if (prefix)
		write(STDERR_FILENO, prefix, ft_strlen(prefix));
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	if (suffix)
		write(STDERR_FILENO, suffix, ft_strlen(suffix));
}

void	print_error_export(char *arg)
{
	print_error("minishell: export: `", arg, "': not a valid identifier\n");
}

void	print_error_cd(void)
{
	write(STDERR_FILENO, "minishell: cd: too many arguments\n", 34);
}

void	print_error_exit_numeric(char *arg)
{
	print_error("minishell: exit: ", arg, ": numeric argument required\n");
}
