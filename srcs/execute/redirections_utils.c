/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 11:47:43 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/14 12:27:12 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_and_close(char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY,
			S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	if (fd == -1)
	{
		g_minishell.error_status = errno;
		return (0);
	}
	close(fd);
	return (1);	
}

int create_files(t_data *data)
{
	int	i;
	int	j;
	int	type;
	char *filename;
//	printf("in cr_files\n");
	i = 0;
	while (i <= data->pars.cmd_nbr - 1)
	{
		if (data->cmds[i].redirs)
		{
			j = 0;
			type = 0;
			type = data->cmds[i].redirs[j].type;
			filename = data->cmds[i].redirs[j].filename;
			while (type >= 0 && type <= 6)
			{
				if (!(open_and_close(filename)))
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
