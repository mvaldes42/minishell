/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:24:14 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/06 23:13:12 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	make_pipe(t_data *data, int rank, int *fd_in) //createpipe
{
	int	new_pipe[2];
	
	dup2(*fd_in, STDIN_FILENO); //putting fd_in as the stdin
	if (*fd_in != 0)
		close(*fd_in);
	if (rank == data->pars.cmd_nbr - 1)
		return (1);
	pipe(new_pipe);
	dup2(new_pipe[1], STDOUT_FILENO);
	if (close(new_pipe[1]) == -1)
		return (0);
	*fd_in = dup(new_pipe[0]);
	close(new_pipe[0]);
	return (1);
}

int	command_executor(t_data *data, int base_rank, int rank, int *fd_in) //cmdparser
{
	int	initial_fd[2];

	save_fds(initial_fd); //set initial_fd to the basic fds
	if (!(make_pipe(data, rank, fd_in)))
		return (0); //sending current rank and fd to create a pipe to write in 
	if (!(make_redirects(data, base_rank, rank, initial_fd)))
		return (0); //check redirects and handle their fds
	if (!(execute(data, rank)))
		return (0);
	set_back_fds(initial_fd); //set back initial fds
	return (1);
}

int	parse_and_exec(t_data *data, int *fd_in, int base_rank, int rank) //pipecheck
{
	while (rank < data->pars.cmd_nbr - 1)
	{
		if (!(command_executor(data, base_rank, rank, fd_in)))
			return (0);
		rank++;
		if (rank < data->pars.cmd_nbr - 1)
			parse_and_exec(data, fd_in, base_rank, rank);
		break ;
	}
	if (rank == data->pars.cmd_nbr - 1)
	{
		if (!(command_executor(data, base_rank, rank, fd_in)))
			return (0);
	}
	return (1);
}

int	navigate_line(t_data *data) //p&x
{
	int	fd_in;

	fd_in = 0;
	if (!(parse_and_exec(data, &fd_in, 0, 0)))
		return (0);
	if (fd_in != 0)
		close(fd_in);
	printf("errno = %d\n", errno);
	return (1);
}
