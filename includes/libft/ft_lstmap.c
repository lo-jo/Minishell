/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:59:24 by elmaleuv          #+#    #+#             */
/*   Updated: 2022/05/20 17:25:22 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*first;

	new_lst = 0;
	if (!f || !del)
		return (NULL);
	while (lst)
	{
		first = ft_lstnew((*f)(lst->content));
		if (!first)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, first);
		lst = lst->next;
	}
	return (new_lst);
}
