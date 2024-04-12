/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:11:14 by ljospin           #+#    #+#             */
/*   Updated: 2023/04/28 13:22:12 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_pipe(t_cmd *cmd, t_minishell *minishell)
{
	cmd->pid = fork();
	config_child_signal();
	if (cmd->pid == -1)
		perror("fork error");
	if (cmd->pid == 0)
	{
		init_io(cmd);
		if (exec_builtin(cmd, cmd->cmd_list[0], minishell) == 1)
		{
			if (cmd->cmd_list[0])
			{
				if (execute(minishell, cmd))
				{
					close_cmd_fd(minishell);
					close(3);
					exit(127);
				}
			}
		}
		close_cmd_fd(minishell);
		free_minishell(minishell);
		free_hash(minishell->hash);
		exit(0);
	}
}
