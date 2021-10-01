/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handling.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 15:27:03 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/01 16:49:03 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	set_initial_fd(int *first_fd)
{
	first_fd = 0;
}

void	close_initial_fd(int *first_fd)
{
	if (first_fd != 0)
		close(first_fd);
}

void	save_fds(int *fd)
{
	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
}

void	set_back_fds(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
}