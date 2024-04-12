/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 10:18:08 by lo                #+#    #+#             */
/*   Updated: 2023/05/02 16:13:41 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_array(char **cmd)
{
	int	i;

	i = 0;
	if (cmd)
	{
		while (cmd[i])
		{
			if (cmd[i])
			{
				free(cmd[i]);
				cmd[i] = NULL;
			}
			i++;
		}
		free(cmd);
		cmd = NULL;
	}
}

void	free_str(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	free_minishell(t_minishell *minishell)
{
	if (minishell->token)
		clear_token(&minishell->token);
	if (minishell->cmd)
		free_array(minishell->cmd);
	if (minishell->dir_list)
		free_array(minishell->env);
	if (minishell->command)
		cmd_clear(&minishell->command, free);
}

void	free_exec_cmd(t_minishell *minishell)
{
	free_str(minishell->input);
	free_minishell(minishell);
	free_hash(minishell->hash);
}

int	free_execute_pb(t_minishell *minishell)
{
	free_str(minishell->input);
	free_minishell(minishell);
	free_hash(minishell->hash);
	return (1);
}
