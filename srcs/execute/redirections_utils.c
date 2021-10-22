/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:47:43 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/22 15:50:32 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_and_close(char *filename, int type)
{
	int	fd;

	if (type != 3 && type != 6)
		return (1);
	fd = open(filename, O_CREAT | O_WRONLY,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd == -1)
	{
		g_error = errno;
		return (0);
	}
	close(fd);
	return (1);
}

/*
** for each > and >> redirection,
** creates a file by opening and closing it
*/

int	create_files(t_data *data)
{
	int		i;
	int		j;
	int		type;
	char	*filename;

	i = 0;
	while (i <= data->pars.cmd_nbr - 1)
	{
		if (data->cmds->redirs_size > 0)
		{
			j = 0;
			type = data->cmds[i].redirs[j].type;
			filename = data->cmds[i].redirs[j].filename;
			while (j < data->cmds[i].redirs_size)
			{
				if (!(open_and_close(filename, type)))
					return (0);
				j++;
				type = data->cmds[i].redirs[j].type;
				filename = data->cmds[i].redirs[j].filename;
			}
		}
		i++;
	}		
	return (1);
}

void	check_heredoc_ctrl_d(int status, char *end)
{
	g_error = WEXITSTATUS(status);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 131)
	{
		printf("bash: warning : \"here document\" on line 1 ended with ");
		printf("end_of_file (instead of %s).\n", end);
	}
	if (g_error == 131)
		g_error = 0;
}
