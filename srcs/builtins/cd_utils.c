/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:40:17 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 12:38:18 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_cwd_err(char *wd, char *buff)
{
	ft_putstr_fd("chdir: error retrieving current directory ", 2);
	ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
	free_str(wd);
	free_str(buff);
	g_exit_code = 1;
	return ;
}

void	ch_dir_err(char *path, char *old_wd, char *old_buff)
{
	simple_err("cd : no such file or directory : ", path, 1);
	free_str(old_wd);
	free_str(old_buff);
	return ;
}
