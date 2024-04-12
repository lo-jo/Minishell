/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 14:55:49 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 12:02:48 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_dollar_delimiter(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0'
		|| c == '\'' || c == '\"' || c == '/')
		return (1);
	return (0);
}

int	get_key_end(char *str, int idx)
{
	while (!is_dollar_delimiter(str[idx]))
			idx++;
	return (idx - 1);
}

int	is_regular_delim(char c)
{
	if (c == '\0' || c == '$')
		return (1);
	return (0);
}

int	find_end(char *str, int i)
{
	while (!is_regular_delim(str[i]))
		i++;
	return (i);
}
