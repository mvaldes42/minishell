/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:29:19 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/21 13:53:09 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_general(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	handle_signals_empty(void)
{
	signal(SIGINT, sig_int_general);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

void	sig_heredoc(int sig)
{
	(void)sig;
	g_minishell.error_status = 1;
	write(1, "\n", 1);
	exit(131);
}

void	sig_quit(int sig)
{
	(void)sig;
	g_minishell.error_status = 131;
	printf("Quit\n");
}

void	sig_int_interactive(int sig)
{
	(void)sig;
	g_minishell.error_status = 130;
	write(1, "\n", 1);
}
