/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:08:15 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 16:27:09 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*parse_redir_out(t_cmd *cmd, t_token *token)
{
	if (token->flag_type == TOKEN_REDIR_OUT)
	{
		token = token->next;
		if (!token)
			return (NULL);
		if (is_ambiguous_redir(token->content, cmd))
			return (NULL);
		else
			redir_out(cmd, token->content);
	}
	else if (token->flag_type == TOKEN_REDIR_OUT_APPEND)
	{
		token = token->next;
		if (!token)
			return (NULL);
		if (is_ambiguous_redir(token->content, cmd))
			return (NULL);
		else
			redir_out_append(cmd, token->content);
	}
	return (token);
}

t_token	*parse_heredoc(t_cmd *cmd, t_token *token, t_minishell *m)
{
	int	i;

	i = 0;
	token = token->next;
	if (!token)
		return (NULL);
	while (cmd->cmd_list[i])
		i++;
	make_here_doc(token->content, m, cmd);
	cmd->cmd_list[i] = ft_strdup(".tmp");
	if (i == 0)
		cmd->pb = 1;
	return (token);
}

t_token	*parse_redir_in(t_cmd *cmd, t_token *token, t_minishell *m)
{
	if (token->flag_type == TOKEN_REDIR_IN)
	{
		token = token->next;
		if (!token)
			return (NULL);
		if (cmd->pb == 1)
			return (token);
		if (is_valid_filename(cmd, token->content))
			return (token);
		else
		{
			cmd->pb = 1;
			cmd->input = 0;
			return (token);
		}
	}
	else if (token->flag_type == TOKEN_HEREDOC)
		token = parse_heredoc(cmd, token, m);
	return (token);
}

t_token	*parse_redir(t_cmd *cmd, t_token *token, t_minishell *m)
{
	token = parse_redir_out(cmd, token);
	if (!token)
		return (NULL);
	token = parse_redir_in(cmd, token, m);
	if (!token)
		return (NULL);
	return (token);
}
