/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:11:31 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/01 10:15:29 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_ambiguous_redir(char *file_name, t_cmd *cmd)
{
	if (file_name[0] == '$')
	{
		print_err(file_name, "ambiguous redirect", 1);
		cmd_clear(&cmd, free);
		return (1);
	}
	return (0);
}

void	redir_out_append(t_cmd *cmd, char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror(file_name);
		return ;
	}
	if (cmd->output != STDOUT_FILENO)
	{
		dup2(fd, cmd->output);
		close(cmd->output);
	}
	cmd->output = fd;
}

void	redir_out(t_cmd *cmd, char *file_name)
{
	int	fd;

	fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file_name);
		return ;
	}
	if (cmd->output != STDOUT_FILENO)
	{
		dup2(fd, cmd->output);
		close(cmd->output);
	}
	cmd->output = fd;
}
