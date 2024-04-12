/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:06:28 by ljospin           #+#    #+#             */
/*   Updated: 2023/04/26 13:53:09 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cmd_lst_size(t_token *token)
{
	int	i;

	i = 0;
	while (token->next)
	{
		i++;
		token = token->next;
	}
	return (i);
}

t_cmd	*parse_pipe(t_cmd *cmd, t_minishell *minishell)
{
	cmd->pipe = 1;
	cmd_addback(&minishell->command, cmd);
	cmd = cmd_new(cmd_lst_size(minishell->token) + 1);
	return (cmd);
}

t_token	*parse_word(t_token *token, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmd_list[i] != NULL)
	{
		while (cmd->cmd_list[i] != NULL)
			i++;
	}
	while (token->flag_type == TOKEN_WORD)
	{
		if (!token->next)
		{
			cmd->cmd_list[i] = ft_strdup(token->content);
			cmd->cmd_list[i + 1] = NULL;
			return (token);
		}
		cmd->cmd_list[i] = ft_strdup(token->content);
		token = token->next;
		i++;
	}
	cmd->cmd_list[i] = NULL;
	return (token->prev);
}
