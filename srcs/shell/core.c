/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljospin <ljospin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:31:05 by lo                #+#    #+#             */
/*   Updated: 2023/05/01 10:32:46 by ljospin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	start_up_shell(void)
{
	char	*user;

	user = getenv("USER");
	ft_putstr_fd(ANSI_MAG, 1);
	ft_putstr_fd("♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡\n", 1);
	ft_putstr_fd("                                           \n", 1);
	ft_putstr_fd("                   o8o               o8o \n", 1);
	ft_putstr_fd("                   `\"'               `\"\' \n", 1);
	ft_putstr_fd("ooo. .oo.  .oo.   oooo  ooo. .oo.   oooo \n", 1);
	ft_putstr_fd("`888P\"Y88bP\"Y88b  `888  `888P\"Y88b  `888 \n", 1);
	ft_putstr_fd(" 888   888   888   888   888   888   888 \n", 1);
	ft_putstr_fd(" 888   888   888   888   888   888   888 \n", 1);
	ft_putstr_fd("o888o o888o o888o o888o o888o o888o o888o\n", 1);
	ft_putstr_fd("♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡\n", 1);
	ft_putstr_fd(ANSI_RESET, 1);
	ft_putstr_fd("\t  W E L C O M E ...     ", 1);
	ft_putstr_fd(user, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(ANSI_MAG, 1);
	ft_putstr_fd("♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡♡\n\n", 1);
	ft_putstr_fd(ANSI_RESET, 1);
}

void	reset_shell(t_minishell *minishell)
{
	minishell->i = 0;
	minishell->end = 0;
	minishell->len = 0;
	minishell->token = NULL;
	minishell->command = NULL;
	minishell->input = NULL;
	minishell->cmd = NULL;
	minishell->dir_list = NULL;
}

void	updateshlvl(t_minishell *minishell)
{
	int		level;
	char	*lvl;

	level = 0;
	if (retrieve_value(minishell->hash, "SHLVL") != NULL)
	{
		level = ft_atoi(retrieve_value(minishell->hash, "SHLVL"));
		hash_delete_duo(minishell->hash, "SHLVL");
	}
	level += 1;
	lvl = ft_itoa(level);
	hash_insert_duo(minishell->hash, "SHLVL", lvl);
	free_str(lvl);
}

void	init_shell(t_minishell *minishell, char **env)
{
	minishell->i = 0;
	minishell->end = 0;
	minishell->len = 0;
	minishell->token = NULL;
	minishell->input = NULL;
	minishell->cmd = NULL;
	minishell->dir_list = NULL;
	minishell->env = NULL;
	minishell->hash = env_to_hash(env);
	minishell->command = NULL;
	updateshlvl(minishell);
}
