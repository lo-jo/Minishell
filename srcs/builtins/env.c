/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:02:23 by lo                #+#    #+#             */
/*   Updated: 2023/05/02 15:59:57 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*fill_key_equals_value(t_hash_item *item)
{
	char	*res;
	char	*temp;

	temp = ft_strjoin(item->key, "=");
	res = ft_strjoin(temp, item->value);
	free(temp);
	return (res);
}

char	**get_env_from_hash(t_minishell *minishell)
{
	int			i;
	int			j;
	t_hash_item	*current;
	t_hash_item	*tmp;
	char		**env;

	i = 0;
	j = 0;
	env = (char **)malloc((sizeof(char *) * minishell->hash->size) + 1);
	if (!env)
		return (NULL);
	while (i < minishell->hash->size)
	{
		current = minishell->hash->items[i];
		while (current != NULL)
		{
			tmp = current->next;
			env[j] = fill_key_equals_value(current);
			current = tmp;
			j++;
		}
		i++;
	}
	env[j] = NULL;
	return (env);
}

void	exec_env(char **cmd, t_minishell *minishell, t_cmd *c)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	if (cmd[1])
	{
		ft_putstr_fd(cmd[0], 2);
		write(2, ": `", 2);
		ft_putstr_fd(cmd[1], 2);
		write(2, "': ", 3);
		ft_putendl_fd("No such file or directory", 2);
		g_exit_code = 127;
		return ;
	}
	else if (!cmd[1])
	{
		minishell->env = get_env_from_hash(minishell);
		while (minishell->env[i])
			ft_putendl_fd(minishell->env[i++], c->output);
		g_exit_code = 0;
		free_array(minishell->env);
	}
}

/*
if env is used with arguments
>> wrongful use of command, return error
else, build array from hash table and print it
update exit status code
*/