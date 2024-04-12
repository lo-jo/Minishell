/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:05:28 by elisemaleuv       #+#    #+#             */
/*   Updated: 2023/04/28 14:17:14 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/***************************************************************************
-------------------------------CREDITS--------------------------------------
In the implementation of our hashtable, we used the DJB2 hash function.
Written by Daniel J. Bernstein (also known as djb), this simple hash function 
dates back to 1991.
This popular hash function is simple to compute, handles risks of collisions,
and produces relevant keys. 
Read more at : https://theartincode.stanis.me/006-djb2/
***************************************************************************/

unsigned long int	hash_function(char *key, unsigned int size)
{
	unsigned long int	hash;
	unsigned int		index;

	hash = 5381;
	index = 0;
	while (key && key[index])
	{
		hash = ((hash << 5) + hash) + key[index];
		index++;
	}
	return (hash % size);
}
