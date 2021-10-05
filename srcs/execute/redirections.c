/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:28:09 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/05 21:13:44 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// error handling
// find a better way to check for redirs when there are pipes
// check if base_rank is useful

void	redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redir_append_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirs(t_data *data, int type, char *filename, int *initial_fd)
{
	if (type == REDIR_OUT)
		redir_out(filename);
	else if (type == REDIR_OUT_A)
		redir_append_out(filename);
	else if (type == REDIR_IN)
		redir_in(filename);
	else if (type == READ_IN)
		exec_read_in(filename, initial_fd);
	(void)data;
}

/*
** for each command, follows the redirs by setting the STDIN and STDOUT
** opens or creates the needed files as it goes
*/

void	make_redirects(t_data *data, int base_rank, int rank, int *initial_fd)
{
	int		i;
	int		j;
	int		type;
	char	*filename;

	i = base_rank;
	while (i <= rank)
	{
		if (data->cmds[i].redirs)
		{
			j = 0;
			type = 0;
			type = data->cmds[i].redirs[j].type;
			filename = data->cmds[i].redirs[j].filename;
			while (type >= 0 && type <= 6)
			{
				handle_redirs(data, type, filename, initial_fd);
				j++;
				type = data->cmds[i].redirs[j].type;
				filename = data->cmds[i].redirs[j].filename;
			}
		}
		i++;
	}
}
