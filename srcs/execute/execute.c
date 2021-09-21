/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/21 15:40:16 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include <fcntl.h>
#include <sys/stat.h>

#include <curses.h>
#include <term.h>

/*
** handle all errors
** EXIT que ce soit builtin/out + garder en memoire le code de sortie d'erreur
** EXIT_SUCCESS et EXIT_FAILURE macros
** should I handle other signals
** handle ctrl D
** handle multiple redirs
**
** Louski :
** bash-3.2$ sort <<
** bash: syntax error near unexpected token `newline'
** oko | oko | oko
** 
*/

/*
** executes a single function
** forks when it's not a builtin
*/

int	execute_fct(t_data *data) //int i??
{
	t_commands	cmd;
	pid_t		pid;

	cmd = data->cmds[0];
	if (cmd.fct.builtin)
	{
		if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
			data->is_exit = TRUE;
		if (!cmd.fct.builtin_ptr(cmd.args, &data->environ))
			return (0); // a preciser
	}
	else
	{
		pid = fork(); // a proteger
		if (pid == 0)
			if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)
				return (0); //error to handle
		waitpid(pid, NULL, 0);
	}
	return (0); // a preciser
}

/*
** executes a single piped function
** the function is already forked
*/

int	execute_piped_fct(t_data *data, int i)
{
	t_commands	cmd;

	cmd = data->cmds[i];
	if (cmd.fct.builtin)
	{
		if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
			data->is_exit = TRUE;
		if (!cmd.fct.builtin_ptr(cmd.args, &data->environ))
			exit (0); // a preciser
	}
	else
	{
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)
			exit (0); //error to handle
	}
	exit (0); // a preciser
}
/*
void check_tty()
{
	int 	fd;
	char	*term_type;
	int		ret;

	term_type = getenv("TERM");		//get terminal type
	ret = tgetent(NULL, term_type);	//initialise termcap library by recovering infos from terminal + A PROTEGER
//	printf("tgetent = %d\n", ret);
//	int 	col = tgetnum("co");
	int 	li = tgetnum("li");
	char *cl_cap; //clean screen
	char *cm_cap;
	cl_cap = tgetstr("cl", NULL); //clean screen
	cm_cap = tgetstr("cm", NULL); //clean screen

//	tputs(cl_cap, 1, putchar);
	tgoto(cm_cap, 5, li);
//	printf("tgetnum co = %d li = %d\n", col, li);

//	tputs(tgoto(cm_cap, col - 2, li), 1, putchar);

//	if (tgetflag("os") == 0)
	fd = ttyslot();
//	tputs(tgoto(cm_cap, 5, 5), 1, putchar);

//	printf("ttyslot = %d\n", fd);
//	printf("ttyname = %s\n", ttyname(fd));
	
}

int get_pos(int *y, int *x) {

 char buf[30]={0};
 int ret, i, pow;
 char ch;

	*y = 0; 
	*x = 0;

 struct termios term, restore;

 tcgetattr(0, &term);
 tcgetattr(0, &restore);
 term.c_lflag &= ~(ICANON|ECHO);
 tcsetattr(0, TCSANOW, &term);

 write(1, "\033[6n", 4);

 for( i = 0, ch = 0; ch != 'R'; i++ )
 {
    ret = read(0, &ch, 1);
    if ( !ret ) {
       tcsetattr(0, TCSANOW, &restore);
       fprintf(stderr, "getpos: error reading response!\n");
       return 1;
    }
    buf[i] = ch;
    printf("buf[%d]: \t%c \t%d\n", i, ch, ch);
 }

 if (i < 2) {
    tcsetattr(0, TCSANOW, &restore);
    printf("i < 2\n");
    return(1);
 }

 for( i -= 2, pow = 1; buf[i] != ';'; i--, pow *= 10)
     *x = *x + ( buf[i] - '0' ) * pow;

 for( i-- , pow = 1; buf[i] != '['; i--, pow *= 10)
     *y = *y + ( buf[i] - '0' ) * pow;

 tcsetattr(0, TCSANOW, &restore);
 return 0;
}

int pain() {
 int x = 0, y = 0;
 get_pos(&y, &x);
 printf("x:%d, y:%d\n", x, y);
 return 0;
}
*/
int	execute(t_data *data)
{
	int			pipe_nb;

//	pain();
	if (check_redir(data) == -1) // a modifier
		return (1); //erreur dramatique
	data->pid = malloc(sizeof(pid_t) * data->pars.cmd_nbr);
	pipe_nb = data->pars.cmd_nbr - 1;
	if (!data->pid)
		printf("malloc error\n");
	if (data->pars.cmd_nbr >= 2)
	{
		piping(data, data->pars.cmd_nbr);
		while (pipe_nb >= 0)
			waitpid(data->pid[pipe_nb--], NULL, 0);
	}
	else
	{
		execute_fct(data); // gerer erreur
	}
	return (1);
}
