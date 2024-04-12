/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 11:35:15 by ljospin           #+#    #+#             */
/*   Updated: 2023/04/04 12:12:59 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_delim(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index] != c)
		index++;
	return (index + 1);
}

t_hash_table	*env_to_hash(char **env)
{
	t_hash_table	*hash_env;
	char			*key;
	char			*value;
	int				delim;
	int				i;

	i = 0;
	hash_env = new_hash((array_len(env)) * 2);
	while (i < (hash_env->size / 2))
	{
		delim = find_delim(env[i], '=');
		key = ft_substr(env[i], 0, delim - 1);
		value = ft_substr(env[i], delim, ft_strlen(env[i]));
		hash_insert_duo(hash_env, key, value);
		i++;
		free(key);
		free(value);
	}
	return (hash_env);
}
