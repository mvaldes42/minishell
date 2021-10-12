/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 15:51:19 by fcavillo         ###   ########.fr       */
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

int	exec_builtout(t_data *data, t_commands cmd)
{
	int		pid;
	int		status;

	errno = CMD_NOT_FOUND;
	if (cmd.fct.fct_path == NULL)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		g_minishell.error_status = errno;
		return (0);
	}
	handle_signals_exec();
	if (pid == 0)
	{
		if (!(execve(cmd.fct.fct_path, cmd.args, data->environ)))
		{
			g_minishell.error_status = errno;
			return (0);
		}
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_minishell.error_status = WIFEXITED(status);
	return (1);
}

int	exec_builtin(t_data *data, t_commands cmd)
{
	if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
		data->is_exit = TRUE;
	if (!cmd.fct.builtin_ptr(cmd.args, &data->environ))
		return (0);
	return (1);
}

int	execute(t_data *data, int nb)
{
	t_commands	cmd;

	cmd = data->cmds[nb];
	if (cmd.fct.builtin)
	{
		if (!(exec_builtin(data, cmd)))
			return (0);
	}
	else
	{
		if (!(exec_builtout(data, cmd)))
			return (0);
	}
	return (1);
}
