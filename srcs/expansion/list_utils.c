/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 13:24:34 by ljospin           #+#    #+#             */
/*   Updated: 2023/04/06 13:24:58 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	list_clear(t_list **list, void (*del)(void *))
{
	t_list	*tmp;

	if (!del || !list)
		return ;
	while (*list)
	{
		tmp = (*list)->next;
		if ((*list)->content)
			free((*list)->content);
		ft_lstdelone(*list, del);
		(*list) = tmp;
	}
}

void	free_list(t_list *list)
{
	t_list	*tmp;

	if (list == NULL)
		return ;
	while (list != NULL)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
	list = NULL;
}
