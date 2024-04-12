/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 17:30:26 by lo                #+#    #+#             */
/*   Updated: 2023/04/20 12:57:59 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	interrupt_child(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", 1);
	g_exit_code = 130;
}

void	quit_child(int signal)
{
	(void)signal;
	simple_err("Quit (core dumped)\n", NULL, 131);
}

void	interrupt_sig(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_code = 130;
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	config_child_signal(void)
{
	signal(SIGINT, interrupt_child);
	signal(SIGQUIT, quit_child);
}

/* Defines behaviour of ctrl C (SIGINT),
** Ignores behaviour of Ctrl \ (SIGQUIT)
** in the parent process. */

void	config_signal(void)
{
	signal(SIGINT, interrupt_sig);
	signal(SIGQUIT, SIG_IGN);
}
