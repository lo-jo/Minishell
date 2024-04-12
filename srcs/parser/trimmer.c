/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimmer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 14:58:27 by lo                #+#    #+#             */
/*   Updated: 2023/05/02 12:07:07 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	trim_quotes(char *input, t_minishell *minishell, int start)
{
	char	*trim;
	int		flag_type;

	flag_type = 0;
	while (is_white_space(input[minishell->i]) && input[minishell->i] != '\0')
		minishell->i++;
	trim = ft_substr(input, start, minishell->end - start);
	if (!trim)
		return ;
	flag_type = token_type(trim);
	add_back_token(&minishell->token, token_new(trim, flag_type));
	minishell->i = minishell->end - 1;
}

void	special_plus_one(char *input, t_minishell *minishell)
{
	char	*trim;
	int		flag_type;

	flag_type = 0;
	minishell->end = minishell->i + 1;
	trim = ft_substr(input, minishell->i, minishell->end - minishell->i);
	if (!trim)
		return ;
	flag_type = token_type(trim);
	add_back_token(&minishell->token, token_new(trim, flag_type));
}

void	special_plus_two(char *input, t_minishell *minishell)
{
	char	*trim;
	int		flag_type;

	flag_type = 0;
	minishell->end = minishell->i + 2;
	trim = ft_substr(input, minishell->i, minishell->end - minishell->i);
	if (!trim)
		return ;
	flag_type = token_type(trim);
	add_back_token(&minishell->token, token_new(trim, flag_type));
	minishell->i += 1;
}

void	regular_trim(char *input, t_minishell *m)
{
	int		start;

	start = m->i;
	quote_loop(m, input);
	m->end = m->i;
	trim_quotes(input, m, start);
}

void	special_trim(char *input, t_minishell *m)
{
	if (input[m->i] == '|')
		special_plus_one(input, m);
	else if ((input[m->i] == '>' && \
	input[m->i + 1] == '>') || (input[m->i] == '<' && \
	input[m->i + 1] == '<'))
		special_plus_two(input, m);
	else if ((input[m->i] == '<' && input[m->i + 1] != '<') || \
	(input[m->i] == '>' && input[m->i + 1] != '>'))
		special_plus_one(input, m);
}
