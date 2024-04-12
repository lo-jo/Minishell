/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:21:33 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 14:36:51 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* adds single command to command list */

void	single_command(t_cmd **comm, t_cmd *cmd, t_token *node, t_minishell *m)
{
	cmd->cmd_list[0] = ft_strdup(node->content);
	cmd->cmd_list[1] = NULL;
	cmd_addback(comm, cmd);
	cmd_addback(comm, init_cmd(cmd_lst_size(m->token) + 1));
}

void	add_cmd_to_list(t_cmd **comm, t_cmd *cmd, t_minishell *minishell)
{
	cmd_addback(comm, cmd);
	cmd_addback(comm, init_cmd(cmd_lst_size(minishell->token) + 1));
}

/* If more than one expression is input, then it is sent for 
* parsing */

void	other_command(t_token *node, t_cmd *cmd, t_minishell *m, t_cmd **comm)
{
	while (node)
	{
		if (node->flag_type == TOKEN_WORD)
			node = parse_word(node, cmd);
		else if (node->flag_type == TOKEN_PIPE)
			cmd = parse_pipe(cmd, m);
		else
			node = parse_redir(cmd, node, m);
		if (node->next)
			node = node->next;
		else
			break ;
	}
	add_cmd_to_list(comm, cmd, m);
}

void	prep_command(t_cmd **comm, t_minishell *minishell)
{
	t_token	*node;
	t_cmd	*cmd;

	node = minishell->token;
	cmd = cmd_new(cmd_lst_size(minishell->token) + 1);
	if (cmd_lst_size(minishell->token) == 0)
		single_command(comm, cmd, node, minishell);
	else
		other_command(node, cmd, minishell, comm);
}
