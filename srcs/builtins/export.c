/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 11:17:19 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 16:41:59 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_var(char *cmd)
{
	int	i;

	i = 1;
	if (ft_isdigit(cmd[0]) == 1)
		return (0);
	while (cmd[i])
	{
		if (ft_isalnum(cmd[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

void	define_empty_var(char *cmd, t_minishell *minishell)
{
	char	*value;

	if (retrieve_value(minishell->hash, cmd) != NULL)
		return ;
	value = ft_strdup("");
	hash_insert_duo(minishell->hash, cmd, value);
	free(value);
}

/* 1. Extract Key and Value strings 
*  2. If key is already found in env, then delete and replace it
*  3. Insert new Key and Value pair in hash table */

void	define_var(char *cmd, t_minishell *minishell)
{
	char	*key;
	char	*value;
	int		len;
	int		equal;
	int		i;

	equal = is_equal(cmd);
	len = ft_strlen(cmd);
	key = ft_substr(cmd, 0, equal);
	value = ft_substr(cmd, equal + 1, len);
	i = 0;
	while (key[i++])
	{
		if (is_valid_var(key) == 0)
		{
			ft_putstr_fd("Minishell : export: `", 2);
			simple_err(key, "\': not a valid identifier", 1);
			break ;
		}
	}
	if (retrieve_value(minishell->hash, key) != NULL)
		hash_delete_duo(minishell->hash, key);
	hash_insert_duo(minishell->hash, key, value);
	free(key);
	free(value);
}

void	export_var(char **cmd, t_minishell *minishell)
{
	int	i;

	i = 1;
	if (cmd[1][0] == '=')
	{
		print_err("export", "\': not a valid identifier", 1);
		return ;
	}
	while (cmd[i])
	{
		if (ft_strchr(cmd[i], '='))
			define_var(cmd[i], minishell);
		else
			define_empty_var(cmd[i], minishell);
		i++;
	}
	g_exit_code = 0;
}

void	exec_export(char **cmd, t_minishell *minishell, t_cmd *c)
{
	int	size;

	size = array_len(cmd);
	if (size == 1)
		exec_env(cmd, minishell, c);
	else
		export_var(cmd, minishell);
}
