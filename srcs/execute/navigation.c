/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:24:14 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/05 18:43:01 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
check if there are redirs, send files to be created
send fds to be redirected
check if pipe, send them to be created and to redirect fds
send commands to be exec 
*/

void	make_pipe(t_data *data, int rank, int *fd_in) //createpipe
{
	int	new_pipe[2];
//	printf("in make_pipe, fd_in = %d\n", *fd_in);
	dup2(*fd_in, STDIN_FILENO); //putting fd_in as the stdin
	if (*fd_in != 0)
		close(*fd_in);
	if (rank == data->pars.cmd_nbr - 1)
		return ;
	pipe(new_pipe);
	dup2(new_pipe[1], STDOUT_FILENO);
	close(new_pipe[1]);
	*fd_in = dup(new_pipe[0]);
	close(new_pipe[0]);
//	printf("out of make pipe\n");
}

void	command_executor(t_data *data, int base_rank, int rank, int *fd_in) //cmdparser
{
	int	initial_fd[2];
//	printf("in command executor, rank = %d doing %s\n", rank, data->cmds[rank].fct.name);
	save_fds(initial_fd); //set initial_fd to the basic fds
	make_pipe(data, rank, fd_in); //sending current rank and fd to create a pipe to write in 
	make_redirects(data, base_rank, rank, initial_fd); //check redirects and handle their fds
	execute(data, rank);
	set_back_fds(initial_fd); //set back initial fds
}

void	parse_and_exec(t_data *data, int *fd_in, int base_rank, int rank) //pipecheck
{
//	printf("in parse_and_exec\n");
	while (rank < data->pars.cmd_nbr - 1)
	{
	//	printf("doing %s\n", data->cmds[rank].fct.name);
		command_executor(data, base_rank, rank, fd_in);
		rank++;
		if (rank < data->pars.cmd_nbr - 1)
			parse_and_exec(data, fd_in, base_rank, rank);
		break ;
	}
	if (rank == data->pars.cmd_nbr - 1)
	{
		command_executor(data, base_rank, rank, fd_in);
	}
}

int	navigate_line(t_data *data) //p&x
{
	int	fd_in;
//	printf("in navigate_line\n");
	set_initial_fd(&fd_in); //initial fd is set to 0, might be replaced
	parse_and_exec(data, &fd_in, 0, 0);
	close_initial_fd(fd_in); //close final input fd if != 0, might be replaced
//	printf("errno = %d\n", errno);
//	if (errno != 0)
//		return (0);
	return (1);
}
