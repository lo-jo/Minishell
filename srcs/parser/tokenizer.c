/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:59:58 by lo                #+#    #+#             */
/*   Updated: 2023/05/02 18:54:40 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	split_token(char *input, t_minishell *minishell)
{
	int	len;

	len = ft_strlen(input);
	while (is_white_space(input[minishell->i]))
		minishell->i++;
	while (minishell->i < len)
	{
		if (!is_splitter(input, minishell->i)
			&& !is_white_space(input[minishell->i]))
			regular_trim(input, minishell);
		if (is_splitter(input, minishell->i))
			special_trim(input, minishell);
		minishell->i++;
	}
}

int	dismiss_input(t_minishell *minishell, char *input)
{
	if (!input)
	{
		free_minishell(minishell);
		print_err("Command line unavailable.", NULL, 1);
		return (1);
	}
	else if (input[0] == '\0')
		return (1);
	while (is_white_space(input[minishell->i]))
	{
		minishell->i++;
		if (minishell->i == (int)ft_strlen(input))
			return (1);
	}	
	return (0);
}

void	update_token_post_exp(t_token *token)
{
	while (token)
	{
		token->flag_type = token_type(token->content);
		token = token->next;
	}
}

void	tokenizer(t_minishell *minishell)
{
	if (!dismiss_input(minishell, minishell->input))
	{
		add_history((const char *)minishell->input);
		split_token(minishell->input, minishell);
		if (!check_grammar(minishell))
			return ;
		expand_token(minishell);
		update_token_post_exp(minishell->token);
		prep_command(&minishell->command, minishell);
		prep_execution(minishell);
	}
}

int	is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}
