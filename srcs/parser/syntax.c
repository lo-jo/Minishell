/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:04:18 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 12:11:59 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_quote(t_token *token)
{
	int	quote_flag;
	int	i;

	quote_flag = -1;
	i = 0;
	while (token->content[i])
	{
		if (quote_flag == -1 && (token->content[i] == '\''
				|| token->content[i] == '\"'))
			quote_flag = i;
		else if (quote_flag > -1
			&& token->content[i] == token->content[quote_flag])
			quote_flag = -1;
		i++;
	}
	if (quote_flag > -1)
	{
		simple_err("Minishell : utility syntax error near unexpected token`",
			token->content, 2);
		return (0);
	}
	return (1);
}

int	is_valid_redir(t_token *token)
{
	if (token->flag_type == TOKEN_REDIR_OUT || token->flag_type == TOKEN_HEREDOC
		|| token->flag_type == TOKEN_REDIR_OUT_APPEND
		|| token->flag_type == TOKEN_REDIR_IN)
	{
		if (!token->next)
		{
			print_err("utility syntax error near unexpected token `newline'",
				NULL, 2);
			return (0);
		}
		else if (token->next->flag_type != TOKEN_WORD)
		{
			print_err("utility syntax error near unexpected token ",
				token->content, 2);
			return (0);
		}
	}
	return (1);
}

int	is_valid_scenario(t_token *token)
{
	if (token->flag_type == TOKEN_PIPE && token->next)
	{
		if (token->next->flag_type > TOKEN_WORD)
		{
			if (token->next->next && token->next->next->flag_type != TOKEN_WORD)
			{
				print_err("utility syntax error near unexpected token `|'",
					NULL, 2);
				return (0);
			}	
		}
	}
	return (1);
}

int	is_valid_pipe(t_token *token, int index)
{
	if (token->flag_type == TOKEN_PIPE)
	{
		if (index == 0 || !token->next)
		{
			print_err("utility syntax error near unexpected token `|'",
				NULL, 2);
			return (0);
		}
	}
	return (1);
}

int	check_grammar(t_minishell *minishell)
{
	t_token	*token_list;
	int		i;

	token_list = minishell->token;
	i = 0;
	while (token_list)
	{
		if (!is_valid_pipe(token_list, i) || !is_valid_redir(token_list)
			|| !is_valid_scenario(token_list) || !is_valid_quote(token_list))
			return (0);
		i++;
		token_list = token_list->next;
	}
	return (1);
}
