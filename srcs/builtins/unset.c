/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:34:15 by elmaleuv          #+#    #+#             */
/*   Updated: 2023/04/27 18:59:28 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset_var(char **cmd, t_minishell *minishell)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (retrieve_value(minishell->hash, cmd[i]) != NULL)
			hash_delete_duo(minishell->hash, cmd[i]);
		else
			return ;
		i++;
	}
}

/*
* unset without argument shall not be interpreted as an error
* 
*/
void	exec_unset(char **cmd, t_minishell *minishell)
{
	int	size;

	size = array_len(cmd);
	if (size == 1)
		return ;
	else
		unset_var(cmd, minishell);
}
