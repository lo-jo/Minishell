/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 18:18:34 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 12:25:41 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_cmd *cmd, char *name, t_minishell *m)
{
	if (!name)
		return (1);
	if (is_builtin(name))
	{
		if (ft_strncmp(name, "cd", 3) == 0)
			exec_cd(cmd->cmd_list, m);
		else if (ft_strncmp(name, "echo", 5) == 0)
			exec_echo(cmd->cmd_list, cmd);
		else if (ft_strncmp(name, "env", 4) == 0)
			exec_env(cmd->cmd_list, m, cmd);
		else if (ft_strncmp(name, "export", 7) == 0)
			exec_export(cmd->cmd_list, m, cmd);
		else if (ft_strncmp(name, "pwd", 4) == 0)
			exec_pwd(cmd);
		else if (ft_strncmp(name, "unset", 6) == 0)
			exec_unset(cmd->cmd_list, m);
		else if (ft_strncmp(name, "exit", 5) == 0)
			exec_exit(cmd->cmd_list, m);
		return (0);
	}
	return (1);
}

void	exec_loop(t_minishell *minishell)
{
	t_cmd	*cmd;
	int		pipe_fd[2];

	if (!minishell->command)
		return ;
	cmd = minishell->command;
	while (cmd->next)
	{
		if (cmd->pipe == 1)
		{
			if (pipe(pipe_fd) == -1)
				perror("Pipe Error");
			cmd->output = pipe_fd[1];
			cmd->next->input = pipe_fd[0];
			exec_pipe(cmd, minishell);
		}
		else
			exec_cmd(cmd, minishell);
		cmd = reset_cmd_fd(cmd);
		cmd = cmd->next;
	}
}

void	prep_execution(t_minishell *minishell)
{
	exec_loop(minishell);
	post_processing(minishell);
	close_cmd_fd(minishell);
	cmd_clear(&minishell->command, free);
	if (access(".tmp", F_OK) == 0)
		unlink(".tmp");
	clear_token(&minishell->token);
}
