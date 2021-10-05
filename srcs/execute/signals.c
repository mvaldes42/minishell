/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:29:19 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/05 21:10:02 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// handle errors and exit statuses

int	term(void)
{
	struct termios	term1;

	tcgetattr(STDIN_FILENO, &term1);
	term1.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
		return (0);
	return (1);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	handle_signals(void)
{
	if (term() == 0)
		return (0);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}

void	sig_new_line(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	sig_heredoc(int sig)
{
	(void)sig;
//	g_minishell.exit_status = 130;
	write(1, "\n", 1);
	exit(130);
}

void	sig_quit(int sig)
{
	(void)sig;
	printf("exit\n");
}

void	handle_signals_exec(void)
{
	signal(SIGINT, sig_new_line);
	signal(SIGQUIT, sig_quit);
}
