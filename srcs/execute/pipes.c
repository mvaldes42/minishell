/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:21:32 by fcavillo          #+#    #+#             */
/*   Updated: 2021/08/31 16:25:12 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"                                                                                                                                                                                                                                                                                        


// pipe apres les forks
// executing several  builtins leads to a stop BECAUSE IT CAN'T CLOSE THE FD WICH IS ALREADY CLOSED IN PIPE_FIRST
/*
int pipe_first(t_data *data, int cmd_nb, int **fd)
{
	int i;
	i = 1;
	printf("in pipe_first\n");
	close(fd[0][0]);
	while (i < cmd_nb - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;

	}
	dup2(fd[0][1], STDOUT_FILENO);
	close(fd[0][1]);
	execute_one(data, 0);
//	execve(data->cmds[0].fct.fct_path, data->cmds[0].args, data->environ);
	return (0);
}
*/

int pipe_first(t_data *data, int **fd)
{
	printf("pipe_first\n");
	pipe(fd[0]); //a proteger
	close(fd[0][0]);
	dup2(fd[0][1], STDOUT_FILENO);
	close(fd[0][1]);
	execute_one(data, 0);
	return (0);	
}
/*
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
	execute_one(data, idx);
//	execve(data->cmds[idx].fct.fct_path, data->cmds[idx].args, data->environ);
	return (0);
}*/

int pipe_middle(t_data *data, int idx, int **fd)
{
	int i;

	pipe(fd[idx]); // a proteger
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
	execute_one(data, idx);
	return (0);
}
/*
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
	execute_one(data, i);
//	execve(data->cmds[i].fct.fct_path, data->cmds[i].args, data->environ);
	return (0);	
}*/

int pipe_last(t_data *data, int idx, int **fd)
{
	int i;

	i = 0;
	close(fd[idx - 1][1]);
	while (i < idx - 1)
	{
		close(fd[i][1]);
		close(fd[i][0]);
		i++;		
	}
	dup2(fd[i][0], STDIN_FILENO);
	close(fd[i][0]);
	i++;
	execute_one(data, i);
	return (0);	
}

int piping(t_data *data, int cmd_nb)
{
	int **fd;
//	pid_t pid[cmd_nb];
	int j;
	int idx;
	
	printf("in piping_beginning\n");
	if (!(fd = malloc(sizeof(int*) * cmd_nb)))
		return (0);
	idx = cmd_nb - 2;
	while (idx >= 0)
	{
		fd[idx--] = malloc(sizeof(int) * 2);
	}
	idx = 0;
/*	while (idx < cmd_nb - 1)
	{
		if (pipe(fd[idx++]) < 0) //chié
		{
			return (1); 
		}
	}*/
	printf("in piping : malloced the fds\n");
	data->pid = malloc(sizeof(pid_t) * cmd_nb);
	if (!data->pid)
		printf("malloc error\n");
	printf("in piping : malloced the pids\n");
	idx = 0;
//	pid[idx] = ft_fork(data, idx, pid[idx]);
//	pid[idx] = 0;
//	if (!data->cmds[idx].fct.builtin)
//		pid[idx] = fork();
//	if (pid[0] == 0 || data->cmds[idx].fct.builtin)
		pipe_first(data, fd);
	printf("did piping_first\n");
	idx = 1;
	while (idx < cmd_nb - 1)
	{
//		ft_fork(data, idx, pid[idx]);
//		pid[idx] = 0;
//		if (!data->cmds[idx].fct.builtin)
//			pid[idx] = fork();		
//		if (pid[idx] == 0 || data->cmds[idx].fct.builtin)
			pipe_middle(data, idx, fd);
		idx++;
	}
	printf("did piping_mid\n");
//	ft_fork(data, idx, pid[idx]);
//	pid[idx] = 0;
//	if (!data->cmds[idx].fct.builtin)
//		pid[idx] = fork();
//	if (pid[idx] == 0 || data->cmds[idx].fct.builtin)
		pipe_last(data, idx, fd);
	printf("did piping_last\n");
	j = idx;
	idx--;
/*	while(idx >= 0)
	{
		close(fd[idx][0]);
		close(fd[idx][1]);
		idx--;
	}*/
	printf("piping_closed\n");
	idx = j;
	while (j <= idx)
		waitpid(data->pid[idx--], NULL, 0);
	printf("piping_waited\n");
	return (0);
}
