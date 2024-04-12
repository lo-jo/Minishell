/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:10:59 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/01 10:15:05 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_filename(t_cmd *cmd, char *file_name)
{
	if (access(file_name, F_OK) != 0)
	{
		print_err(file_name, "no such file or directory", 1);
		return (0);
	}
	else if (access(file_name, R_OK | W_OK) != 0)
	{
		print_err(file_name, "Permission denied", 1);
		return (0);
	}
	else
	{
		redir_in(cmd, file_name);
		return (1);
	}
}

int	redir_in(t_cmd *cmd, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
		return (0);
	if (cmd->input != STDIN_FILENO)
	{
		dup2(cmd->input, fd);
		close(cmd->input);
	}
	cmd->input = fd;
	return (1);
}
