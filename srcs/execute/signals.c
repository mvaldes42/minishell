/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:29:19 by fcavillo          #+#    #+#             */
/*   Updated: 2021/09/21 18:14:04 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	term(void)
{
	struct termios	term1;

	tcgetattr(STDIN_FILENO, &term1);
	term1.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
		return ;//error to handle
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

/*

int	ft_putint(int c)
{
	write(1, &c, 1);
	return (0);
}

void	term() {
  struct termios term1;

	tcgetattr(STDIN_FILENO, &term1);
  if (tcgetattr(STDIN_FILENO, &term1) != 0)
    perror("tcgetattr() error");
  else {
    printf("the original end-of-file character is x'%02x'\n",
           term1.c_cc[VEOF]);
    term1.c_cc[VEOF] = 'z';
//	term1.c_lflag[ECHOCTL] = 0;
	term1.c_lflag &= ~ECHOCTL;
//	printf("%ctl = %d\n", term1.c_lflag[ECHOCTL]);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
      perror("tcsetattr() error");
    if (tcgetattr(STDIN_FILENO, &term1) != 0)
      perror("tcgetattr() error");
    else
      printf("the new end-of-file character is x'%02x'\n",
             term1.c_cc[VEOF]);
 }



** I need to get the current cursor position


void	sig_handler(int sig)
{
//	int		ret;
//	int		li;
//	char	*cm_cap;
//	char	*term_type;

//	term();
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
}*/
