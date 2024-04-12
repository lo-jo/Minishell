/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:22:43 by lo                #+#    #+#             */
/*   Updated: 2023/04/06 14:06:30 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	token_type(char *input)
{
	if (!ft_strncmp(input, "|", 1) && ft_strncmp(input, "||", 2))
		return (TOKEN_PIPE);
	if (!ft_strncmp(input, ">", 1) && ft_strncmp(input, ">>", 2))
		return (TOKEN_REDIR_OUT);
	if (!ft_strncmp(input, "<", 1) && ft_strncmp(input, "<<", 2))
		return (TOKEN_REDIR_IN);
	if (!ft_strncmp(input, ">>", 2))
		return (TOKEN_REDIR_OUT_APPEND);
	if (!ft_strncmp(input, "<", 1))
		return (TOKEN_HEREDOC);
	else
		return (TOKEN_WORD);
}

void	clear_token(t_token **list)
{
	t_token	*token;
	t_token	*temp;

	token = *list;
	if (token == NULL)
		return ;
	while (token != NULL)
	{
		temp = token->next;
		free(token->content);
		free(token);
		token = temp;
	}
	*list = NULL;
}

t_token	*token_last(t_token *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	add_back_token(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (token)
	{
		if (*token)
		{
			tmp = token_last(*token);
			tmp->next = new;
			new->prev = tmp;
		}
		else
			*token = new;
	}
}

t_token	*token_new(char *content, int flag_type)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new->content = content;
	new->flag_type = flag_type;
	new->i = 0;
	new->end = 1;
	new->list = NULL;
	new->dollar = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
