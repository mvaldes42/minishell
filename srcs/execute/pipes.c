/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:21:32 by fcavillo          #+#    #+#             */
/*   Updated: 2021/09/02 12:21:15 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"                                                                                                                                                                                                                                                                                        

int	**ft_malloc_fds(int cmd_nb) //a proteger
{
	int i;
	int **fd;
	
	if (!(fd = malloc(sizeof(int*) * (cmd_nb - 1))))
		return (0);
	i = cmd_nb - 2;
	while (i >= 0)
	{
		fd[i--] = malloc(sizeof(int) * 2);
	}
	return (fd);
}

int pipe_first(t_data *data, int **fd)
{
	pipe(fd[0]); //a proteger
	data->pid[0] = fork(); //a proteger
	if (data->pid[0] == 0)
	{
		close(fd[0][0]);
		dup2(fd[0][1], STDOUT_FILENO);
		close(fd[0][1]);
		execute_piped_fct(data, 0);
	}
	return (0);	
}

int pipe_middle(t_data *data, int idx, int **fd)
{
	int i;

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
	return (0);
}

int pipe_last(t_data *data, int idx, int **fd)
{
	int i;

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
	return (0);	
}

int piping(t_data *data, int cmd_nb)
{
	int **fd;
	int j;
	int idx;
	
	fd = ft_malloc_fds(cmd_nb); //gerer erreur
/*	if (!(fd = malloc(sizeof(int*) * (cmd_nb - 1))))
		return (0);
	idx = cmd_nb - 2;
	while (idx >= 0)
	{
		fd[idx--] = malloc(sizeof(int) * 2);
	}*/
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
	while(idx >= 0)
	{
		close(fd[idx][0]);
		close(fd[idx][1]);
		idx--;
	}
	idx = j;
	return (0);
}
