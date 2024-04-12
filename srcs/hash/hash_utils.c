/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:04:59 by elisemaleuv       #+#    #+#             */
/*   Updated: 2023/04/21 14:04:18 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

/* inserer une nouvelle paire key / value dans la hash
* on se deplace juste avec des index en cherchant une petite place vide
* et on initialise
* Might be a problem when the spot in the list is already used by 
* a variable we already set
* if thats the case, it is replaced in the same spot by the new one
* otherwise, the list is scanned all the way down to add back the duo 
* if that the first time of ever inserting anything then it is just set*/

void	hash_insert_duo(t_hash_table *hash, char *key, char *value)
{
	t_hash_item		*new_item;
	t_hash_item		*prev_item;
	int				index;

	new_item = hash_new_item(key, value);
	index = hash_function(new_item->key, hash->size);
	prev_item = hash->items[index];
	if (prev_item)
	{
		if (ft_strncmp(prev_item->key, key, ft_strlen(key) + 1) == 0)
		{
			free(prev_item->value);
			prev_item->value = ft_strdup(value);
			free_hash_item(new_item);
		}
		else
		{
			while (prev_item->next != NULL)
				prev_item = prev_item->next;
			prev_item->next = new_item;
			prev_item->next->next = NULL;
		}
	}
	else
		hash->items[index] = new_item;
}

void	get_node_and_delete(t_hash_item *current, char *key)
{
	t_hash_item	*temp;

	while (current->next != NULL)
	{
		if (ft_strncmp(current->next->key, key, ft_strlen(key) + 1) == 0)
		{
			temp = current->next;
			current->next = current->next->next;
			free_hash_item(temp);
			return ;
		}
		current = current->next;
	}
}

/* supprimer une paire de la hash table with key */
void	hash_delete_duo(t_hash_table *hash, char *key)
{
	int			index;
	t_hash_item	*current;

	index = hash_function(key, hash->size);
	current = hash->items[index];
	if (current == NULL)
		return ;
	else if (current->next == NULL
		&& ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
	{
		free_hash_item(current);
		hash->items[index] = NULL;
		return ;
	}
	else if (current->next != NULL
		&& ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
	{
		hash->items[index] = current->next;
		free_hash_item(current);
		return ;
	}
	else
		get_node_and_delete(current, key);
}
