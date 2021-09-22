/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:21:32 by fcavillo          #+#    #+#             */
/*   Updated: 2021/09/22 14:50:56 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**ft_malloc_fds(int cmd_nb)
{
	int	i;
	int	**fd;

	fd = malloc(sizeof(int *) * (cmd_nb - 1));
	ft_memset(fd, 0, sizeof(fd));
	if (!(fd))
		return (0);
	i = cmd_nb - 2;
	while (i >= 0)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
			return (0);
		i--;
	}
	return (fd);
}

int	pipe_first(t_data *data, int **fd)
{
	errno = CMD_NOT_FOUND;
	if (!data->cmds[0].fct.builtin && data->cmds[0].fct.fct_path == NULL)
		error_handling();
	pipe(fd[0]); //a proteger
	data->pid[0] = fork(); //a proteger
	if (data->pid[0] == 0)
	{
		close(fd[0][0]);
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][1]);
		execute_piped_fct(data, 0);
	}
	return (1);
}

int	pipe_middle(t_data *data, int idx, int **fd)
{
	int	i;

	errno = CMD_NOT_FOUND;
	if (!data->cmds[idx].fct.builtin && data->cmds[idx].fct.fct_path == NULL)
		error_handling();
	pipe(fd[idx]); // a proteger
	data->pid[idx] = fork();
	if (data->pid[idx] == 0)
	{
		i = 0;
		close(fd[idx - 1][1]);
		close(fd[idx][0]);
		while (i < idx - 1)
		{
			close(fd[i][1]);
			close(fd[i][0]);
			i++;
		}
		dup2(fd[idx - 1][0], STDIN_FILENO);
		dup2(fd[idx][1], STDOUT_FILENO);
		close(fd[idx - 1][0]);
		close(fd[idx][1]);
		execute_piped_fct(data, idx);
	}
	return (1);
}

int	pipe_last(t_data *data, int idx, int **fd)
{
	int	i;
	errno = CMD_NOT_FOUND;
	if (!data->cmds[idx].fct.builtin && data->cmds[idx].fct.fct_path == NULL)
		error_handling();
	i = 0;
	data->pid[idx] = fork();
	if (data->pid[idx] == 0)
	{
		close(fd[idx - 1][1]);
		while (i < idx - 1)
		{
			close(fd[i][1]);
			close(fd[i][0]);
			i++;
		}
		dup2(fd[idx - 1][0], STDIN_FILENO);
		close(fd[idx - 1][0]);
		i++;
		execute_piped_fct(data, i);
	}
	return (1);
}

int	piping(t_data *data, int cmd_nb)
{
	int	**fd;
	int	j;
	int	idx;

	fd = ft_malloc_fds(cmd_nb);
	if (fd == 0)
	{
		// free ce qui a été malloc si une erreur de malloc arrive pendant
		return (0); // On doit close les FD avant de return ?
	}
	pipe_first(data, fd);
	idx = 1;
	while (idx < cmd_nb - 1)
	{
		pipe_middle(data, idx, fd);
		idx++;
	}
	pipe_last(data, idx, fd);
	j = idx;
	idx--;
	while (idx >= 0)
	{
		close(fd[idx][0]);
		close(fd[idx][1]);
		idx--;
	}
	return (1);
}
