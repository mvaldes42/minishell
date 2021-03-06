/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:28:09 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/22 18:51:05 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd == -1)
	{
		g_error = errno;
		return (0);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (1);
}

int	redir_append_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd == -1)
	{
		g_error = errno;
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd == -1)
	{
		g_error = errno;
		return (0);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (1);
}

int	handle_redirs(t_data *data, int type, char *filename, int *initial_fd)
{
	if (type == REDIR_OUT)
	{
		if (!(redir_out(filename)))
			return (0);
	}
	else if (type == REDIR_OUT_A)
	{
		if (!(redir_append_out(filename)))
			return (0);
	}
	else if (type == REDIR_IN)
	{
		if (!(redir_in(filename)))
			return (0);
	}
	else if (type == READ_IN)
	{
		if (!(exec_read_in(data, filename, initial_fd)))
			return (0);
	}
	return (1);
}

/*
** for each command, follows the redirs by setting the stdin and stdout
*/

int	make_redirects(t_data *data, int rank, int *initial_fd)
{
	int		j;
	int		type;
	char	*filename;

	if (data->cmds[rank].redirs_size > 0)
	{
		j = 0;
		type = data->cmds[rank].redirs[j].type;
		filename = data->cmds[rank].redirs[j].filename;
		while (j < data->cmds[rank].redirs_size)
		{
			if (!(handle_redirs(data, type, filename, initial_fd)))
				return (0);
			j++;
			type = data->cmds[rank].redirs[j].type;
			filename = data->cmds[rank].redirs[j].filename;
		}
	}
	return (1);
}
