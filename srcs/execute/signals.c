/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:29:19 by fcavillo          #+#    #+#             */
/*   Updated: 2021/09/14 16:42:19 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putint(int c)
{
	write(1, &c, 1);
	return (0);
}

/*
** I need to get the current cursor position
*/

void	sig_handler(int sig)
{
	int		ret;
	int		li;
	char	*cm_cap;
	char	*term_type;

	term_type = getenv("TERM");//get terminal type
	ret = tgetent(NULL, term_type);//initialise termcap library by recovering infos from terminal + A PROTEGER
	cm_cap = tgetstr("cm", NULL);//get the termcap to move cursor
	li = tgetnum("li");
	tputs(tgoto(cm_cap, 38, li + 1), 1, ft_putint);//38 a changer en fonction du prompt - tputs execute tgoto 
	write(1, "  ", 2);
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
