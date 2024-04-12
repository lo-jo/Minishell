/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:51:16 by ljospin           #+#    #+#             */
/*   Updated: 2023/04/27 14:02:39 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd	*reset_cmd_fd(t_cmd *cmd)
{
	if (cmd->output != STDOUT_FILENO)
		close(cmd->output);
	if (cmd->input != STDIN_FILENO)
		close(cmd->input);
	return (cmd);
}

void	close_fd(t_minishell *minishell)
{
	t_cmd	*cmd;

	close(STDERR_FILENO);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(3);
	cmd = minishell->command;
	if (cmd)
	{
		while (cmd->next)
		{
			if (cmd->input != STDIN_FILENO)
				close(cmd->input);
			if (cmd->output != STDOUT_FILENO)
				close(cmd->output);
			if (cmd->pipe)
				close(cmd->next->input);
			cmd = cmd->next;
		}
	}
}

void	close_cmd_fd(t_minishell *minishell)
{
	t_cmd	*cmd;

	cmd = minishell->command;
	if (cmd)
	{
		while (cmd->next)
		{
			if (cmd->input != STDIN_FILENO)
				close(cmd->input);
			if (cmd->output != STDOUT_FILENO)
				close(cmd->output);
			cmd = cmd->next;
		}
	}
}

void	init_io(t_cmd *cmd)
{
	if (cmd->input != STDIN_FILENO)
	{
		dup2(cmd->input, STDIN_FILENO);
		close(cmd->input);
	}
	if (cmd->output != STDOUT_FILENO)
	{
		dup2(cmd->output, STDOUT_FILENO);
		if (cmd->pipe && cmd->next)
			close(cmd->next->input);
	}
}
