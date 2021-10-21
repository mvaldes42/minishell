/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/21 16:29:44 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include <fcntl.h>
#include <sys/stat.h>

#include <curses.h>
#include <term.h>

int	exec_builtout(t_data *data, t_commands cmd, int nb)
{
	int		pid;
	int		status;

	(void)data;
	errno = CMD_NOT_FOUND;
	if (cmd.fct.fct_path == NULL)
		g_error = 134;
	if (cmd.fct.fct_path == NULL && data->pars.cmd_nbr - 1 == nb)
		return (0);
	pid = fork();
	if (pid == -1)
	{
		g_error = errno;
		return (0);
	}
	signal(SIGINT, sig_int_interactive);
	if (pid == 0)
		exit(execve(cmd.fct.fct_path, cmd.args, data->environ));
	waitpid(pid, &status, 0);
	g_error = WEXITSTATUS(status);
	return (1);
}

int	exec_builtin(t_data *data, t_commands cmd)
{
	if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
		data->is_exit = TRUE;
	if (!cmd.fct.builtin_ptr(cmd.args, cmd.nbr_args, &data->environ))
		return (0);
	return (1);
}

int	execute(t_data *data, int nb)
{
	t_commands	cmd;

	cmd = data->cmds[nb];
	signal(SIGQUIT, sig_quit);
	if (cmd.fct.builtin)
	{
		if (!(exec_builtin(data, cmd)))
			return (0);
	}
	else
	{
		if (!(exec_builtout(data, cmd, nb)))
			return (0);
	}
	g_error = 0;
	return (1);
}
