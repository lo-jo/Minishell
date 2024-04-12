/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:58:37 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 12:19:44 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_command_error(char **env_, char *path, t_minishell *minishell)
{
	free_str(minishell->input);
	clear_history();
	free_array(env_);
	free_str(path);
	free_hash(minishell->hash);
	free_minishell(minishell);
	return (g_exit_code);
}

int	launch_execution(char *path, t_cmd *cmd, char **env_, t_minishell *m)
{
	if (execve(path, cmd->cmd_list, env_) == -1)
	{
		print_err(cmd->cmd_list[0], strerror(errno), 127);
		free_command_error(env_, path, m);
		return (g_exit_code);
	}
	return (0);
}

int	execute(t_minishell *minishell, t_cmd *cmd)
{
	char	**dir_list;
	char	**env_;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	if (!cmd->cmd_list[0])
		return (1);
	if (cmd->pb == 1)
		return (free_execute_pb(minishell));
	env_ = get_env_from_hash(minishell);
	if (execve(cmd->cmd_list[0], cmd->cmd_list, env_) == -1)
	{
		dir_list = find_path_list(minishell, cmd);
		if (dir_list == NULL)
			return (free_command_error(env_, path, minishell));
		path = find_executable(dir_list, cmd->cmd_list[i]);
		if (path == NULL)
			return (free_command_error(env_, path, minishell));
		return (launch_execution(path, cmd, env_, minishell));
	}
	return (0);
}

void	fork_and_config(t_cmd *cmd)
{
	cmd->pid = fork();
	config_child_signal();
}

void	exec_cmd(t_cmd *cmd, t_minishell *minishell)
{
	if (cmd->prev)
		exec_pipe(cmd, minishell);
	else
	{
		if (exec_builtin(cmd, cmd->cmd_list[0], minishell) == 1
			&& cmd->cmd_list[0] != NULL && !cmd->cmd_list[0][0] == 0)
		{
			fork_and_config(cmd);
			if (cmd->pid == 0)
			{
				init_io(cmd);
				if (execute(minishell, cmd))
				{
					cmd_clear(&minishell->command, free);
					close_fd(minishell);
					close(3);
					exit (127);
				}
				free_exec_cmd(minishell);
				close_fd(minishell);
				exit(0);
			}
		}
	}
}
