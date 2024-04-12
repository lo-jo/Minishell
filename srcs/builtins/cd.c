/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 18:22:43 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 19:13:40 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_pwd(t_minishell *minishell)
{
	char	*pwd;
	char	*pwd_buff;

	pwd_buff = NULL;
	pwd = getcwd(pwd_buff, 1024);
	if (pwd == NULL)
		get_cwd_err(pwd, pwd_buff);
	if (retrieve_value(minishell->hash, "PWD") != NULL)
		hash_delete_duo(minishell->hash, "PWD");
	hash_insert_duo(minishell->hash, "PWD", pwd);
	free_str(pwd);
	free_str(pwd_buff);
}

void	change_dir(char *path, t_minishell *minishell)
{
	char	*old_buff;
	char	*old_wd;

	old_buff = NULL;
	old_wd = getcwd(old_buff, 1024);
	if (old_wd == NULL)
		get_cwd_err(old_wd, old_buff);
	hash_insert_duo(minishell->hash, "OLDPWD", old_wd);
	if (chdir(path) == -1)
	{
		simple_err("cd : no such file or directory : ", path, 1);
		free_str(old_wd);
		free_str(old_buff);
		free_str(path);
		return ;
	}
	update_pwd(minishell);
	free_str(old_wd);
	free_str(old_buff);
	free_str(path);
	g_exit_code = 0;
}

void	get_to_dir(char *path, t_minishell *minishell, char *key)
{
	path = ft_strdup(retrieve_value(minishell->hash, key));
	if (path == NULL)
	{
		simple_err("cd : no such file or directory : ", path, 1);
		free_str(path);
		return ;
	}
	change_dir(path, minishell);
}

void	exec_cd(char **cmd, t_minishell *minishell)
{
	char	*path;
	int		len;

	path = NULL;
	len = array_len(cmd);
	if (len > 2)
	{
		print_err("cd : too many arguments", NULL, 1);
		return ;
	}
	else if (len == 1 || (ft_strncmp(cmd[1], "~", 1) == 0))
		get_to_dir(path, minishell, "HOME");
	else if (len == 2 && (ft_strncmp(cmd[1], "-", 1) == 0))
	{
		get_to_dir(path, minishell, "OLDPWD");
		ft_putendl_fd(retrieve_value(minishell->hash, "OLDPWD"), 1);
	}
	else
	{
		path = ft_strdup(cmd[1]);
		change_dir(path, minishell);
	}
}
