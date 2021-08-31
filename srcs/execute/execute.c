/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/02 15:30:16 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include <fcntl.h>
#include <sys/stat.h>

//handle all errors

/*
** checks wether the function is a builtin -> no fork
** or a builtout -> fork
*/

int	ft_fork(t_data *data, int i, pid_t *pid)
{
	if (!data->cmds[i].fct.builtin)
	{
			printf("builtout\n");
			pid[i] = fork();
			return (pid[i]);
	}
	printf("builtin\n");
	return (0);
}

/*executes a builtin if it is, a builtout if it is not*/

int	execute_one(t_data *data, int i)
{
	t_commands	cmd;
	int			fd;

	fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, \
	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	dprintf(fd, "hello fd\n");
	cmd = data->cmds[i];
	if (cmd.fct.builtin)
	{
		dprintf(fd, "hello builtin\n");
		if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
		{
			if (data->pars.cmd_nbr == 1)
			{
				data->is_exit = TRUE;
				dprintf(fd, "hello real exit\n");
				close(fd);
				return (1);
			}
		}
		else if (!cmd.fct.builtin_ptr(cmd.args, &data->environ))
		{
			dprintf(fd, "hello random builtin\n");
			return (0);
		}
		dprintf(fd, "hello exit in pipe\n");
	}
	else
	{
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)
			return (0); //error to handle
	}
	close(fd);
	return (1);
}

int	execute(t_data *data)
{
	pid_t		pid;

	if (data->pars.cmd_nbr >= 2)
	{
		piping(data, data->pars.cmd_nbr);
	}
	else
	{
		if (!data->cmds[0].fct.builtin)
		{
			pid = fork();
			if (pid == 0)
				if (!execute_one(data, 0))
					return (0);
			waitpid(pid, NULL, 0);
		}
		else
			if (!execute_one(data, 0))
				return (0);
	}
	return (1);
}
