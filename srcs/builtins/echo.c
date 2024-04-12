/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:37:18 by lo                #+#    #+#             */
/*   Updated: 2023/04/27 20:34:03 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_echo(char **cmd, t_cmd *comm, int i, int n)
{
	if (cmd[i][0] != 0)
		ft_putstr_fd(cmd[i], comm->output);
	if (cmd[i + 1] && cmd[i][0] != 0)
		write(comm->output, " ", 1);
	else if (!cmd[i + 1] && !n)
		write(comm->output, "\n", 1);
}

int	option_n(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-')
	{
		i += 1;
		if (cmd[i] != 'n')
			return (0);
		while (cmd[i] == 'n')
			i++;
	}
	if (cmd[i] == 0)
		return (1);
	return (0);
}

void	exec_echo(char **cmd, t_cmd *comm)
{
	int	n;
	int	i;

	i = 1;
	n = 0;
	while (cmd[i] && option_n(cmd[i]))
	{
		n = 1;
		i += 1;
	}
	if (!cmd[i])
	{
		if (!n)
			write (comm->output, "\n", 1);
		g_exit_code = 0;
		return ;
	}
	while (cmd[i])
	{
		print_echo(cmd, comm, i, n);
		i++;
	}
	g_exit_code = 0;
}
/*
imprime les arg après "echo" suivi de \n
l'option -n execute la commande sans \n
si echo sans arg, give prompt back
si echo -n sans arg, print \n */