/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:17:20 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 16:10:41 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	post_processing(t_minishell *minishell)
{
	t_cmd	*cmd;

	if (minishell->command->pid == -1)
		return ;
	cmd = minishell->command;
	while (cmd->next != NULL)
	{
		waitpid(cmd->pid, &g_exit_code, 0);
		cmd = cmd->next;
	}
	if (WIFSIGNALED(g_exit_code))
		g_exit_code = WTERMSIG(g_exit_code) + 128;
	if (WIFEXITED(g_exit_code))
		g_exit_code = WEXITSTATUS(g_exit_code);
}
