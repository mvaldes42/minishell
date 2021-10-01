/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:24:14 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/01 17:20:25 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
check if there are redirs, send files to be created
send fds to be redirected
check if pipe, send them to be created and to redirect fds
send commands to be exec 
*/

void	make_pipe(t_data *data, int rank, int *fd_in)
{
	int	new_pipe[2];

	dup2(*fd_in, STDIN_FILENO);
	if (*fd_in != 0)
		close(*fd_in);
	
}

void	command_executor(t_data *data, int b_rank, int rank, int *fd_in)
{
	int	initial_fd[2];
	
	save_fds(initial_fd); //set initial_fd to the basic fds

	make_pipe(data, rank, fd_in);

	set_back_fds(initial_fd); //set back initial fds
}

void	parse_and_exec(t_data *data, int *fd_in, int base_rank)
{
	int rank;

	rank = base_rank;
	command_executor(data, base_rank, rank, fd_in);
}

void	navigate_line(t_data *data)
{
	int	fd_in;
	
	set_initial_fd(&fd_in); //initial fd is set to 0, might be replaced

	parse_and_exec(data, &fd_in, 0);
	
	close_end_fd(fd_in);  //close final input fd if != 0, mightbe replaced
}