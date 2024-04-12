/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:22:33 by lo                #+#    #+#             */
/*   Updated: 2023/05/02 14:21:52 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_code;

void	loop_interactive(t_minishell *minishell)
{
	while (1)
	{
		config_signal();
		minishell->input = readline("Minishell$>");
		if (!minishell->input)
		{
			clear_history();
			free_str(minishell->input);
			ft_putendl_fd("exit", 1);
			return ;
		}
		tokenizer(minishell);
		free(minishell->input);
		free_minishell(minishell);
		reset_shell(minishell);
	}
}

void	launch_check(int argc, char **env)
{
	if (!*env)
	{
		ft_putendl_fd("Error: Empty env\n", 2);
		exit (2);
	}
	if (argc != 1)
	{
		print_err("Invalid nb of arg", NULL, 1);
		exit (2);
	}
}	

int	main(int argc, char **argv, char **env)
{
	t_minishell	minishell;

	(void)argv;
	g_exit_code = 0;
	config_signal();
	launch_check(argc, env);
	start_up_shell();
	if (argc == 1)
	{	
		init_shell(&minishell, env);
		loop_interactive(&minishell);
	}
	free_minishell(&minishell);
	clear_history();
	if (minishell.hash)
		free_hash(minishell.hash);
	return (g_exit_code);
}
