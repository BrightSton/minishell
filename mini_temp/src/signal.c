/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djang <djang@student.42gyeongsan.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 01:04:29 by djang             #+#    #+#             */
/*   Updated: 2025/05/18 01:04:31 by djang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


volatile sig_atomic_t g_signal_num = 0;

void	sigint_handler(int signo)
{
	(void)signo;
	write(1,"\n",1);
	rl_on_new_line();
	rl_replace_line("",0);
	rl_redisplay();
}

void	set_signal(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}