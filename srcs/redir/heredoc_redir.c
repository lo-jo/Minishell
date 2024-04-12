/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elmaleuv <elmaleuv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:08:58 by ljospin           #+#    #+#             */
/*   Updated: 2023/05/02 16:35:12 by elmaleuv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	interrupt_doc(int signum)
{
	if (signum == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		g_exit_code = 130;
		exit (130);
	}
}

void	here_doc_eof(char *delim, int fd, t_cmd *cmd, t_minishell *m)
{
	ft_putstr_fd("Minishell: warning: here-document delimited by ", 2);
	ft_putstr_fd("end of file (wanted `", 2);
	ft_putstr_fd(delim, 2);
	ft_putstr_fd("\')\n", 2);
	clear_history();
	close(fd);
	free_hash(m->hash);
	cmd_clear(&cmd, free);
	free_minishell(m);
	exit(0);
}

void	create_from_input(int fd, char *delim, t_minishell *m, t_cmd *cmd)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, interrupt_doc);
	input = readline("heredoc >");
	while (1)
	{	
		if (!input)
			here_doc_eof(delim, fd, cmd, m);
		if (!input || (!ft_strncmp(input, delim, ft_strlen(delim))
				&& !input[ft_strlen(delim)]))
			break ;
		ft_putendl_fd(input, fd);
		free(input);
		input = readline("heredoc >");
	}
	free_str(input);
	close(fd);
	free_hash(m->hash);
	cmd_clear(&cmd, free);
	free_minishell(m);
	exit(0);
}

void	make_here_doc(char *delim, t_minishell *m, t_cmd *cmd)
{
	int	tmp_fd;
	int	pid;

	tmp_fd = open(".tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd == -1)
		perror("invalid fd");
	pid = fork();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	if (pid == 0)
		create_from_input(tmp_fd, delim, m, cmd);
	waitpid(pid, &g_exit_code, 0);
	if (WIFSIGNALED(g_exit_code))
		g_exit_code = WTERMSIG(g_exit_code) + 128;
	if (WIFEXITED(g_exit_code) && WEXITSTATUS(g_exit_code) == 130)
		g_exit_code = 130;
}
