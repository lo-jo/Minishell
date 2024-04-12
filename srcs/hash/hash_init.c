/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:05:22 by elisemaleuv       #+#    #+#             */
/*   Updated: 2023/04/06 13:30:46 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* initialise un nouvel element contenant une paire key / value.*/

t_hash_item	*hash_new_item(char *key, char *value)
{
	t_hash_item	*item;

	item = malloc(sizeof(t_hash_item));
	if (!item)
		return (NULL);
	item->key = ft_strdup(key);
	item->value = ft_strdup(value);
	item->next = NULL;
	return (item);
}

t_hash_table	*new_hash(int array_len)
{
	t_hash_table	*hash;
	int				i;

	i = 0;
	hash = (t_hash_table *)malloc(sizeof(t_hash_table));
	if (!hash)
		return (NULL);
	hash->size = array_len;
	hash->items = ft_calloc(sizeof(t_hash_table), array_len);
	while (i < array_len)
	{
		hash->items[i] = NULL;
		i++;
	}
	return (hash);
}
