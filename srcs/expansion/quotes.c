/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 18:16:25 by ljospin           #+#    #+#             */
/*   Updated: 2023/04/17 14:47:43 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	keep_one_remove_other(t_token *token, char c)
{
	char	**dquote;
	int		i;
	t_list	*list;

	list = NULL;
	i = 0;
	dquote = ft_split(token->content, c);
	if (dquote[0] == NULL)
		ft_lstadd_back(&list, ft_lstnew(strdup("")));
	while (dquote[i])
	{
		ft_lstadd_back(&list, ft_lstnew(dquote[i]));
		i++;
	}
	free(dquote);
	free(token->content);
	token->content = join_expanded(list);
	if ((ft_lstsize(list)) > 1)
		free_list(list);
	else
	{
		free(list->content);
		free(list);
	}
}

/*
* 3. Once variable expansion is completed, remove unecessary quotes.
*    a - INSIDE DOUBLE QUOTES >
* keep single quotes, remove ALL double quotes
*
* CAS PARTICULIER ATTENTION >echo "'hi'"hello""
* 
*    b - INSIDE SINGLE QUOTES > 
* remove ALL simple quotes, keep double quotes
*/

void	remove_quotes(t_token *token)
{
	int	i;
	int	keep_single;

	keep_single = 0;
	i = 0;
	while (token->content[i])
	{
		if (token->content[i] == '\"')
		{
			keep_one_remove_other(token, '\"');
			keep_single = 1;
			break ;
		}
		else if (token->content[i] == '\'' && keep_single == 0)
		{	
			keep_one_remove_other(token, '\'');
			break ;
		}
		i++;
	}
}

/*
* 1. check type of quotes 
* if ' token->flag_type = 1 (no expand)
* if " token->flag_type = 0 (expand)
*/

void	define_quote_type(t_token *token)
{
	int	i;

	i = 0;
	while (token->content[i])
	{
		if (token->content[i] == '\'')
		{
			token->dollar = 1;
			break ;
		}
		else if (token->content[i] == '\"')
		{
			token->dollar = 0;
			break ;
		}
		i++;
	}
}
