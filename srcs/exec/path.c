/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:04:33 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 13:39:12 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* At this point we have extracted the directory list from path
* and should look something like this :
* /mnt/nfs/homes/ljospin/bin
* /mnt/nfs/homes/ljospin/bin
* /usr/local/sbin
* /usr/local/bin
* /....
* With this function we are going to test every path possible
* for the command
* ex : cat
* test each path possible with access
* to do that we need to join cat to the path so it looks like this :
* /mnt/nfs/homes/ljospin/bin/cat
*/

char	*find_executable(char **dir_list, char *command)
{
	char	*exec_test;
	char	*cmd;
	int		i;

	i = 0;
	cmd = ft_strjoin("/", command);
	if (!cmd)
		return (NULL);
	while (dir_list[i])
	{
		exec_test = ft_strjoin(dir_list[i], cmd);
		if (is_dir(exec_test))
			return (dir_err(dir_list, command, exec_test, cmd));
		if (check_access(exec_test))
			return (valid_access(dir_list, cmd, exec_test));
		free(exec_test);
		i++;
	}
	free_str(cmd);
	free_array(dir_list);
	not_found_error(command);
	return (NULL);
}

char	**find_path_list(t_minishell *minishell, t_cmd *cmd)
{
	char	*path;

	path = retrieve_value(minishell->hash, "PATH");
	if (path == NULL)
	{
		print_err(cmd->cmd_list[0], "command not found", 127);
		return (NULL);
	}
	return (ft_split(path, ':'));
}
