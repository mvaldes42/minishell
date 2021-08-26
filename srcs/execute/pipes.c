/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:21:32 by fcavillo          #+#    #+#             */
/*   Updated: 2021/08/26 14:39:43 by fcavillo         ###   ########.fr       */
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
//	printf("In pipe mid for cmd %d, I should keep [%d][0] and [%d][1] open\n", idx + 1, idx - 1, idx);
	i = 0;
	close(fd[idx - 1][1]);
	close(fd[idx][0]);
	while (i < idx - 1)
	{
//		printf("closing all fd[%d]\n", i);
		close(fd[i][1]);
		close(fd[i][0]);
		i++;		
	}
	i = cmd_nb - 2;
//	printf("mid mid\n");
	while (i > idx)
	{
//		printf("closing all fd[%d]\n", i);
		close(fd[i][0]);
		close(fd[i][1]);
		i--;
	}
	dup2(fd[idx - 1][0], STDIN_FILENO);
	dup2(fd[idx][1], STDOUT_FILENO);
	close(fd[idx - 1][0]);
	close(fd[idx][1]);
//	printf("i'm gonna launch %s\n", data->cmds[idx].fct.fct_path);
	execve(data->cmds[idx].fct.fct_path, data->cmds[idx].args, data->environ);
	return (0);
}

int pipe_last(t_data *data, int cmd_nb, int **fd)
{
	int i;
//	printf("In pipe last, cmd_nb = %d\n", cmd_nb);
	i = 0;
	close(fd[cmd_nb - 2][1]);
	while (i < cmd_nb - 2)
	{
//		printf("pipe last here - I am closing smthg\n");
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
//	printf("for the last one, reading from fd[%d][0]\n", i);
	dup2(fd[i][0], STDIN_FILENO);
	close(fd[i][0]);
	i++;
//	printf("executing for last %s\n", data->cmds[i].fct.fct_path);
	execve(data->cmds[i].fct.fct_path, data->cmds[i].args, data->environ);
	return (0);	
}

int piping_mother(t_data *data, int cmd_nb, int **fd)
{
	int idx;
	pid_t pid[cmd_nb];
	int j;
	//FORK AU DEBUT TROUDUC
	
	idx = 0;
/*	while (idx < cmd_nb - 1)
	{
//		printf("gonna fork for cmd nb %d\n", idx + 1);
		pid[idx] = fork();
		idx++;
	}*/
	pid[0] = fork(); // a proteger
	if (pid[0] == 0)
		pipe_first(data, cmd_nb, fd);
	idx = 1;
	while (idx < cmd_nb - 1)
	{
//		printf("gonna fork for cmd nb %d\n", idx + 1);
		pid[idx] = fork();
		if (pid[idx] == 0)
			pipe_middle(data, idx, cmd_nb, fd);
		idx++;
	}
	pid[idx] = fork();
	if (pid[idx] == 0)
		pipe_last(data, cmd_nb, fd);
	j = 0;
	while (j <= idx)
	{
		printf("waiting for beautiful command number %d\n", j + 1);
		waitpid(pid[j], NULL, 0);
		printf("done waiting for beautiful command number %d\n", j + 1);
//		j++;
		idx--;
	}
	printf("donzo mom\n");
	return (0);
}

int		piping(t_data *data, int cmd_nb)
{
	int **fd;
	int idx;
	pid_t pid;

	
	fd = malloc(sizeof(int) * cmd_nb);
	idx = cmd_nb - 2;
	while (idx >= 0)
	{
		fd[idx--] = malloc(sizeof(int) * 2);
	}
	idx = 0;
	while (idx < cmd_nb - 1)
	{
		if (pipe(fd[idx++]) < 0)
		{
			return (1); // fermer tout ce qui est ouvert
		}
	}
	pid = fork();
	if (pid == 0)
	{
		piping_mother(data, cmd_nb, fd);
	}
	idx--;
	while(idx >= 0)
	{
		close(fd[idx][0]);
		close(fd[idx][1]);
		idx--;
	}
//	waitpid(pid, NULL, 0);
/*	pid = waitpid(pid, &status, WUNTRACED); //waiting for a status change
		while (!WIFEXITED(status) && !WIFSIGNALED(status)) //while status is not exit or killed
		  pid = waitpid(pid, &status, WUNTRACED);*/

	return (0);
}

void	pipe_in(t_data *data, int *fd)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	execve(data->cmds[0].fct.fct_path, data->cmds[0].args, data->environ);
}

void	pipe_out(t_data *data, int *fd)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	execve(data->cmds[1].fct.fct_path, data->cmds[1].args, data->environ);
}

int		single_piping(t_data *data)
{
	int	fd[2];
	pid_t	pid1;
	pid_t	pid2;

	pipe(fd);
	pid1 = fork(); //(a proteger)
	if (pid1 == 0)
		pipe_in(data, fd);
	pid2 = fork(); //a proteger
	if (pid2 == 0)
		pipe_out(data, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);	
}

static void	set_pipe(int i, t_data *data, int fd, int fds[2])
{
	(void)i;
	(void)data;
	dup2(fd, 0);
	dup2(fds[1], 1);
	close(fds[1]);
	close(fds[0]);
}

int	multi_piping(t_data *data, int i)
{
	int		fds[2];
	int		fd;
	pid_t	pid;

	fd = 0;
	i++;
	while (i-- != 0)
	{
		pipe(&fd);
		pid = fork();
		if (pid == 0)
		{
			set_pipe(i, data, fd, fds);
			execve(data->cmds[i].fct.fct_path, data->cmds[i].args, data->environ);
//			exec_builtin(i, data, true);
		}
		waitpid(pid, NULL, 0);
		close(fds[1]);
		fd = fds[0];
		i++;
	}
	return (i);
}

int	pipingnumerox(t_data *data, int nb)
{
	int i;
	
	i = 0;
	if (nb == 2)
		single_piping(data);
	else
	{
		while (i < nb - 1)
		{
			multi_piping(data, i);
			i++;
		}
	}
	return (0);
}
