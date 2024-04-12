/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 14:24:41 by ljospin           #+#    #+#             */
/*   Updated: 2023/04/27 20:32:47 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

long long int	ft_atol(char *str)
{
	int				i;
	int				sign;
	long long int	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

static int	check_numeric_code(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd[i])
		return (0);
	while (cmd[i] == '-' || cmd[i] == '+')
		i++;
	if (i > 1)
		return (0);
	while (cmd[i])
	{
		if (!(cmd[i] >= '0' && cmd[i] <= '9'))
			return (0);
		i++;
	}
	if (ft_atol(cmd) > INT_MAX || ft_atol(cmd) < INT_MIN)
		return (0);
	return (1);
}

static void	free_minish_content(t_minishell *minishell)
{
	if (minishell->hash)
		free_hash(minishell->hash);
	clear_history();
	free(minishell->input);
	free_minishell(minishell);
}

void	exec_exit(char **cmd, t_minishell *minishell)
{
	if (!cmd[1])
		g_exit_code = 0;
	else
	{
		if (cmd[2])
		{
			g_exit_code = 2;
			ft_putendl_fd("exit : too many arguments", 2);
		}
		else if (check_numeric_code(cmd[1]) == 0)
		{
			g_exit_code = 2;
			ft_putendl_fd("exit : numeric argument required", 2);
		}
		else if (check_numeric_code(cmd[1]) == 1)
			g_exit_code = ft_atoi(cmd[1]);
	}
	free_minish_content(minishell);
	exit(g_exit_code);
}
