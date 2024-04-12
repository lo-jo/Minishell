/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_hunt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 03:23:14 by elisemaleuv       #+#    #+#             */
/*   Updated: 2023/04/06 13:27:41 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* gets the value from the key in the hash table
- takes the key string
- runs the hash function on that
- obtains hash code to find index of where it sleeps
-> retrieves the content in the array item at the hash code index
*/

char	*retrieve_value(t_hash_table *hash, char *key)
{
	int			key_size;
	int			hashcode;
	t_hash_item	*item_tmp;

	hashcode = hash_function(key, hash->size);
	item_tmp = hash->items[hashcode];
	if (!key)
		return (NULL);
	key_size = ft_strlen((const char *)key);
	while (item_tmp != NULL)
	{
		if (!ft_strncmp(item_tmp->key, key, key_size))
			return (item_tmp->value);
		item_tmp = item_tmp->next;
	}
	return (NULL);
}
