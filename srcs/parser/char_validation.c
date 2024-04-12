/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:05:42 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 19:14:03 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_white_space(char c)
{
	if (c == '\r' || c == '\n' || c == '\v' || c == '\t'
		|| c == '\f' || c == ' ' || c == '\0')
		return (1);
	else
		return (0);
}

int	is_splitter(char *c, int i)
{
	if ((c[i] == '>' && c[i + 1] == '>')
		|| (c[i] == '<' && c[i + 1] == '<'))
		return (1);
	else if (c[i] == '|' || c[i] == '<' || c[i] == '>')
		return (1);
	return (0);
}

int	is_splittr(char *c, int i, t_minishell *m)
{
	if ((c[i] == '>' && c[i + 1] == '>')
		|| (c[i] == '<' && c[i + 1] == '<'))
		return (1);
	else if (c[i] == '|' || c[i] == '<' || c[i] == '>')
		return (1);
	else if ((c[i] == '\"' && (c[i + 1] == '\'' || c[i + 1] == '$'))
		|| (c[i] == '\'' && (c[i + 1] == '\"' || c[i + 1] == '$')))
	{
		if ((m->i + 1) != '\0')
			m->i++;
		return (1);
	}
	return (0);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

void	quote_loop(t_minishell *m, char *input)
{
	int		flag;
	char	match;

	flag = 0;
	match = 0;
	while (input[m->i])
	{
		if (is_quote(input[m->i]))
		{
			if (flag == 1 && match == input[m->i])
				flag = 0;
			else
			{
				flag = 1;
				if (match == 0)
					match = input[m->i];
			}
		}
		if ((flag == 0 && is_white_space(input[m->i]))
			|| (flag == 0 && is_splittr(input, m->i, m)))
			break ;
		m->i++;
	}
}
