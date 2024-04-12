/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:05:25 by elisemaleuv       #+#    #+#             */
/*   Updated: 2023/04/06 13:29:00 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_hash_item(t_hash_item *item)
{
	if (item->key != NULL)
		free(item->key);
	if (item->value != NULL)
		free(item->value);
	if (item)
		free(item);
}

void	free_hash(t_hash_table *hash)
{
	int			i;
	t_hash_item	*current;
	t_hash_item	*tmp;

	i = 0;
	while (i < hash->size)
	{
		current = hash->items[i];
		while (current)
		{
			tmp = current->next;
			free_hash_item(current);
			current = tmp;
		}
		i++;
	}
	free(hash->items);
	free(hash);
}
