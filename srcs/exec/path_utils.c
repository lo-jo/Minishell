/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 13:06:40 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 13:40:30 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

int	check_access(char *exec_test)
{
	int	retaccess;

	retaccess = access(exec_test, F_OK | X_OK);
	if (retaccess == 0)
	{
		g_exit_code = 0;
		return (1);
	}
	else if (retaccess != 0)
		g_exit_code = 126;
	return (0);
}

char	*dir_err(char **dir, char *comm, char *test, char *cmd)
{
	free_array(dir);
	not_found_error(comm);
	free(test);
	if (cmd)
		free(cmd);
	return (NULL);
}

char	*valid_access(char **dir_list, char *cmd, char *exec_test)
{
	free_array(dir_list);
	free_str(cmd);
	return (exec_test);
}

void	not_found_error(char *command)
{
	if (!ft_strchr(command, '/'))
	{
		usleep(200);
		print_err(command, "command not found", 127);
	}
	else if (is_dir(command))
		print_err(command, "is a directory", 126);
	else if (access(command, F_OK) != 0)
		print_err(command, "no such file or directory", 127);
	else if (access(command, F_OK | X_OK) != 0)
		print_err(command, strerror(errno), 126);
}
