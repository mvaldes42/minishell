/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:24:14 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/22 15:43:43 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** checks if each command exists and displays error messages
*/

void	check_commands(t_data *data)
{
	int			i;
	t_commands	cmd;

	i = 0;
	if (data->pars.cmd_nbr > 1)
	{
		while (i < data->pars.cmd_nbr - 1)
		{
			cmd = data->cmds[i];
			if (cmd.fct.fct_path == NULL && !cmd.fct.builtin)
				printf("minishell: command not found\n");
			i++;
		}
	}
}

/*
** sets fd_in as the stdin
** gets it back at 0
** if there is a pipe, creates it
** sets pipe_out as stdout
** sets original fd_in as pipe_in
*/

int	make_pipe(t_data *data, int rank, int *fd_in)
{
	int	new_pipe[2];

	dup2(*fd_in, STDIN_FILENO);
	if (*fd_in != 0)
	{
		g_error = errno;
		close(*fd_in);
	}
	if (rank == data->pars.cmd_nbr - 1)
		return (1);
	pipe(new_pipe);
	dup2(new_pipe[1], STDOUT_FILENO);
	if (close(new_pipe[1]) == -1)
	{
		g_error = errno;
		return (0);
	}
	*fd_in = dup(new_pipe[0]);
	if (close(new_pipe[0]) == -1)
	{
		g_error = errno;
		return (0);
	}
	return (1);
}

/*
** set the fds for this command, based on the current 0 and 1
** makes a pipe by setting the stdin as the current one,
** and the stdout as inside the pipe
** sets the stdout for redirections
** executes the cmd
** sets back the fds to their respective roles for this command
*/

int	command_executor(t_data *data, int rank, int *fd_in)
{
	int	initial_fd[2];

	save_fds(initial_fd);
	if (!(make_pipe(data, rank, fd_in)))
		return (set_back_fds(initial_fd));
	if (!(make_redirects(data, rank, initial_fd)))
		return (set_back_fds(initial_fd));
	if (g_error == 130)
	{
		set_back_fds(initial_fd);
		return (1);
	}
	if (!(execute(data, rank)))
		return (set_back_fds(initial_fd));
	set_back_fds(initial_fd);
	return (1);
}

/*
** executes a command
** recursive if more than one
*/

int	parse_and_exec(t_data *data, int *fd_in, int rank)
{
	while (rank < data->pars.cmd_nbr - 1)
	{
		command_executor(data, rank, fd_in);
		rank++;
		if (rank < data->pars.cmd_nbr - 1)
		{
			if (!(parse_and_exec(data, fd_in, rank)))
				return (0);
		}
		break ;
	}
	if (rank == data->pars.cmd_nbr - 1)
	{
		if (!(command_executor(data, rank, fd_in)))
			return (0);
	}
	return (1);
}

/*
** creates an original base stdin
** creates the files for the > and >> redirections
** checks for the non-existant commands
** sends the command line to p&x
** closes the original stdin if changed
*/

int	navigate_line(t_data *data)
{
	int	fd_in;

	fd_in = 0;
	create_files(data);
	check_commands(data);
	if (!(parse_and_exec(data, &fd_in, 0)) || g_error != 0)
		return (0);
	if (fd_in != 0)
		close(fd_in);
	return (1);
}
