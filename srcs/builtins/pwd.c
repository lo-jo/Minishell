/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:21:04 by lo                #+#    #+#             */
/*   Updated: 2023/05/02 12:51:20 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_pwd(t_cmd *cmd)
{
	char	*buff;
	char	*curr_wd;

	buff = NULL;
	curr_wd = getcwd(buff, 1024);
	if (curr_wd != NULL)
	{
		ft_putendl_fd(curr_wd, cmd->output);
		g_exit_code = 0;
		free(curr_wd);
	}
	else
	{
		ft_putstr_fd("pwd: error retrieving current directory ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		simple_err("No such file or directory", NULL, 1);
		return ;
	}	
	free(buff);
}
