/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_exp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 16:44:34 by ljospin           #+#    #+#             */
/*   Updated: 2023/04/22 17:10:49 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
* Expand_value sends each expanded expression individually
* to seperate nodes 
* ex : hi$USER$HOME
* Becomes a list that goes like this :
* - hi
* - ljospin
* - /mnt/nfs/homes/ljospin
* Where each expression is joined together
*/

char	*join_expanded(t_list *expanded_list)
{
	t_list	*list;
	t_list	*tmp;
	char	*ho;

	list = expanded_list;
	if (ft_lstsize(expanded_list) == 1)
		return (ft_strdup(list->content));
	while (list != NULL)
	{
		if (list && list->next)
		{
			ho = ft_strjoin(list->content, list->next->content);
			free(list->next->content);
			list->next->content = ho;
			tmp = expanded_list;
			expanded_list = list->next;
			free(tmp->content);
		}
		list = list->next;
	}
	return (expanded_list->content);
}

/*
* Gets the expanded value of the keyword placed after $
* First the function delimits the keyword 
* then, looks for it in the hashtable
* if found, the expanded value is stored inside a string 
* and sent to a linked list
* If no expansion from the keyword can be performed,
* then, an empty string is sent to the list
*/
void	retrieve_expansion(t_minishell *minishell, t_token *token)
{
	char	*key;

	key = NULL;
	token->end = get_key_end(token->content, token->i);
	key = ft_substr(token->content, token->i, token->end - token->i + 1);
	if (retrieve_value(minishell->hash, key))
		ft_lstadd_back(&token->list,
			ft_lstnew(ft_strdup(retrieve_value(minishell->hash, key))));
	else if (retrieve_value(minishell->hash, key) == NULL)
		ft_lstadd_back(&token->list, ft_lstnew(ft_strdup("")));
	token->i = token->end;
	free_str(key);
}

void	extract_rest(t_token *token)
{
	char	*extract;

	token->end = find_end(token->content, token->i);
	if (token->end == token->i)
		token->end += 1;
	extract = ft_substr(token->content, token->i, token->end - token->i);
	ft_lstadd_back(&token->list, ft_lstnew(extract));
	token->i = token->end - 1;
}

void	expand_value(t_token *token, t_minishell *minishell)
{
	while (token->content[token->i])
	{
		if (token->content[token->i] == '$'
			&& token->content[token->i + 1] != '\"')
		{
			token->i++;
			retrieve_expansion(minishell, token);
		}
		else
			extract_rest(token);
		token->i++;
	}
	free(token->content);
	token->content = join_expanded(token->list);
	if ((ft_lstsize(token->list)) > 1)
		free_list(token->list);
	else
	{
		free(token->list->content);
		free(token->list);
		token->list = NULL;
	}
}

void	exp_dollar(t_token *token, int idx, t_minishell *minishell)
{
	if (token->content[idx + 1] == '?')
	{
		free(token->content);
		token->content = ft_itoa(g_exit_code);
	}
	else
		expand_value(token, minishell);
}
