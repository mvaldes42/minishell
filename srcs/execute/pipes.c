/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:21:32 by fcavillo          #+#    #+#             */
/*   Updated: 2021/08/22 19:04:54 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"                                                                                                                                                                                                                                                                                        

int pipe_first(t_data *data, int cmd_nb, int **fd)
{
	int i;
//	printf("In pipe first\n");
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
	printf("In pipe mid, I should keep [%d][0] and [%d][1] open\n", idx - 1, idx);
	i = 0;
	close(fd[idx - 1][1]);
	close(fd[idx][0]);
	while (i < idx - 1)
	{
		printf("closing all fd[%d]\n", i);
		close(fd[i][1]);
		close(fd[i][0]);
		i++;		
	}
	i = cmd_nb - 2;
	printf("mid mid\n");
	while (i > idx)
	{
		printf("closing all fd[%d]\n", i);
		close(fd[i][0]);
		close(fd[i][1]);
		i--;
	}
	dup2(fd[idx - 1][0], STDIN_FILENO);
	dup2(fd[idx][1], STDOUT_FILENO);
	close(fd[idx - 1][0]);
	close(fd[idx][1]);
	printf("i'm gonna launch %s\n", data->cmds[idx].fct.fct_path);
	execve(data->cmds[idx].fct.fct_path, data->cmds[idx].args, data->environ);
	return (0);
}

int pipe_last(t_data *data, int cmd_nb, int **fd)
{
	int i;
	printf("In pipe last, cmd_nb = %d\n", cmd_nb);
	i = 0;
	close(fd[cmd_nb - 2][1]);
	while (i < cmd_nb - 2)
	{
//		printf("pipe last here - I am closing smthg\n");
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	printf("for the last one, reading from fd[%d][0]\n", i);
	dup2(fd[i][0], STDIN_FILENO);
	close(fd[i][0]);
	i++;
	printf("executing for last %s\n", data->cmds[i].fct.fct_path);
	execve(data->cmds[i].fct.fct_path, data->cmds[i].args, data->environ);
	return (0);	
}

int piping_mother(t_data *data, int cmd_nb, int **fd)
{
	int idx;
	int pid[cmd_nb];
	int j;
	
	idx = 0;
	pid[0] = fork(); // a proteger
	if (pid[0] == 0)
		pipe_first(data, cmd_nb, fd);
	idx = 1;
	while (idx < cmd_nb - 1)
	{
		printf("gonna fork for cmd nb %d\n", idx + 1);
		pid[idx] = fork();
		if (pid[idx] == 0)
			pipe_middle(data, idx, cmd_nb, fd);
		idx++;
	}
	pid[idx] = fork();
	if (pid[idx] == 0)
		pipe_last(data, cmd_nb, fd);
	printf("waiting for the %d kids\n", idx + 1);
	j = 0;
	while (j <= idx)
	{
		printf("waiting for beautiful command number %d\n", j + 1);
		waitpid(pid[j], NULL, 0);
		printf("done waiting for beautiful command number %d\n", j + 1);
		j++;
	}
	printf("donzo mom\n");
	return (0);
}

int		piping(t_data *data, int cmd_nb)
{
	int **fd;
	int idx;
	int pid;
	
	fd = malloc(sizeof(int) * cmd_nb);
//	printf("Malloced fd of size %d\n", cmd_nb);
	idx = cmd_nb - 2;
	while (idx >= 0)
	{
		fd[idx--] = malloc(sizeof(int) * 2);
//		printf("Malloced fd[%d] of size 2\n", idx + 1);
	}
	idx = 0;
	while (idx < cmd_nb - 1)
	{
//		printf("gonna pipe\n");
		if (pipe(fd[idx++]) < 0)
		{
//			printf("piped\n");
			return (1); // fermer tout ce qui est ouvert
		}
	}
	pid = fork();
	if (pid == 0)
	{
//		printf("going into piping_mommy\n");
		piping_mother(data, cmd_nb, fd);
	}
	idx--;
	while(idx >= 0)
	{
		printf("in grandma, closing [%d]\n", idx);
		close(fd[idx][0]);
		close(fd[idx][1]);
		idx--;
	}
//	printf("heyy\n");
	waitpid(pid, NULL, 0);
	printf("donzo\n");
	return (0);
}