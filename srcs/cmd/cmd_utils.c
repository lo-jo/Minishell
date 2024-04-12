/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:03:25 by ljospin           #+#    #+#             */
/*   Updated: 2023/04/27 13:27:13 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cmd_delone(t_cmd *cmd, void (*del)(void *))
{
	if (!del || !cmd)
		return ;
	if (cmd)
		(*del)(cmd);
}

void	cmd_clear(t_cmd **cmd, void (*del)(void *))
{
	t_cmd	*tmp;

	if (!del || !cmd)
		return ;
	while (*cmd)
	{
		tmp = (*cmd)->next;
		if ((*cmd)->cmd_list)
			free_array((*cmd)->cmd_list);
		cmd_delone(*cmd, del);
		(*cmd) = tmp;
	}
}

void	cmd_addback(t_cmd **list, t_cmd *new)
{
	t_cmd	*tmp;

	if (list)
	{
		if (*list != NULL)
		{
			tmp = *list;
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
			new->prev = tmp;
			new->next = NULL;
		}
		else
			(*list) = new;
	}
}

t_cmd	*init_cmd(int len)
{
	t_cmd	*new_cmd;
	int		i;

	i = 0;
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->cmd_list = (char **)malloc(sizeof(t_token) * len + 1);
	while (i < len)
		new_cmd->cmd_list[i++] = NULL;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	new_cmd->pipe = false;
	new_cmd->pid = -1;
	new_cmd->pb = 0;
	return (new_cmd);
}

t_cmd	*cmd_new(int len)
{
	t_cmd	*new_cmd;

	new_cmd = init_cmd(len + 1);
	*new_cmd->cmd_list = NULL;
	new_cmd->id = 0;
	new_cmd->next = NULL;
	new_cmd->prev = NULL;
	new_cmd->output = STDOUT_FILENO;
	new_cmd->input = STDIN_FILENO;
	new_cmd->pipe = 0;
	new_cmd->pid = -1;
	new_cmd->pb = 0;
	return (new_cmd);
}
