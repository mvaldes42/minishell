/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/05 18:36:17 by fcavillo         ###   ########.fr       */
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
** * bash-3.2$ sort <<
** bash: syntax error near unexpected token `newline'
** * oko | oko | oko
** * ls > hey | pwd > hoy tries to execute hoy ?
** * cd .. sends back too far ?
** * cat < hey | grep e
** * how to know if a fct has redirs
*/


void	exec_builtout(t_data *data, t_commands cmd)
{
	int		pid;
	int		status;
//	errno = CMD_NOT_FOUND; ?
	if (cmd.fct.fct_path == NULL)
		return ;
	pid = fork(); // a proteger
	if (pid == 0)
	{
		execve(cmd.fct.fct_path, cmd.args, data->environ);
	}
	waitpid(pid, &status, 0);
	//set a status ?
}

void	exec_builtin(t_data *data, t_commands cmd)
{
	if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
		data->is_exit = TRUE;
	if (!cmd.fct.builtin_ptr(cmd.args, &data->environ))
		return ;
}

void	execute(t_data *data, int nb)
{
	t_commands	cmd;
//	printf("in execute, nb = %d so %s\n", nb, data->cmds[nb].fct.name);
	cmd = data->cmds[nb];
	if (cmd.fct.builtin)
	{
		exec_builtin(data, cmd);
	}
	else
	{
		exec_builtout(data, cmd);
	}
}
