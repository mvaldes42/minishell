/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:21:32 by fcavillo          #+#    #+#             */
/*   Updated: 2021/08/26 18:03:21 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"                                                                                                                                                                                                                                                                                        


// pipe apres les forks


int pipe_first(t_data *data, int cmd_nb, int **fd)
{
	int i;
	i = 1;
	close(fd[0][0]);
	while (i < cmd_nb - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	dup2(fd[0][1], STDOUT_FILENO);
	close(fd[0][1]);
	execve(data->cmds[0].fct.fct_path, data->cmds[0].args, data->environ);
	return (0);
}

int pipe_middle(t_data *data, int idx, int cmd_nb, int **fd)
{
	int i;
	i = 0;
	close(fd[idx - 1][1]);
	close(fd[idx][0]);
	while (i < idx - 1)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i++;		
	}
	i = cmd_nb - 2;
	while (i > idx)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i--;
	}
	dup2(fd[idx - 1][0], STDIN_FILENO);
	dup2(fd[idx][1], STDOUT_FILENO);
	close(fd[idx - 1][0]);
	close(fd[idx][1]);
	execve(data->cmds[idx].fct.fct_path, data->cmds[idx].args, data->environ);
	return (0);
}

int pipe_last(t_data *data, int cmd_nb, int **fd)
{
	int i;
	i = 0;
	close(fd[cmd_nb - 2][1]);
	while (i < cmd_nb - 2)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	dup2(fd[i][0], STDIN_FILENO);
	close(fd[i][0]);
	i++;
	execve(data->cmds[i].fct.fct_path, data->cmds[i].args, data->environ);
	return (0);	
}

int piping(t_data *data, int cmd_nb)
{
	int **fd;
	pid_t pid[cmd_nb];
	int j;
	int idx;

	fd = malloc(sizeof(int*) * cmd_nb);
	idx = cmd_nb - 2;
	while (idx >= 0)
	{
		fd[idx--] = malloc(sizeof(int) * 2);
	}
	idx = 0;
	while (idx < cmd_nb - 1)
	{
		if (pipe(fd[idx++]) < 0) //chié
		{
			return (1); 
		}
	}
	idx = 0;

	pid[0] = fork(); // a proteger
	if (pid[0] == 0)
		pipe_first(data, cmd_nb, fd);
	idx = 1;
	while (idx < cmd_nb - 1)
	{
		pid[idx] = fork();
		if (pid[idx] == 0)
			pipe_middle(data, idx, cmd_nb, fd);
		idx++;
	}
	pid[idx] = fork();
	if (pid[idx] == 0)
		pipe_last(data, cmd_nb, fd);
	j = idx;
	idx--;
	while(idx >= 0)
	{
		close(fd[idx][0]);
		close(fd[idx][1]);
		idx--;
	}
	idx = j;
	while (j <= idx)
		waitpid(pid[idx--], NULL, 0);
	return (0);
}
