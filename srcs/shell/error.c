/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:04:39 by lo                #+#    #+#             */
/*   Updated: 2023/05/02 12:03:33 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//ERROR POUR COMMANDES, RETURN SPECIFIC ERROR CODE
//GENERAL ERROR, PRINT MSG

void	simple_err(char *msg, char *suffix, int error)
{
	ft_putstr_fd(msg, 2);
	if (suffix != NULL)
		ft_putendl_fd(suffix, 2);
	if (suffix == NULL)
		write(1, "\n", 2);
	g_exit_code = error;
}

void	print_err(char *msg, char *suffix, int error)
{
	ft_putstr_fd("Minishell: ", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	if (suffix != NULL)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(suffix, STDERR_FILENO);
	}
	if (suffix == NULL)
		write(1, "\n", STDERR_FILENO);
	g_exit_code = error;
}
