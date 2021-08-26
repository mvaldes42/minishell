/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 16:21:32 by fcavillo          #+#    #+#             */
/*   Updated: 2021/08/26 17:45:10 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"                                                                                                                                                                                                                                                                                        


// Delete grand mere
// pipe apres les forks
// close tou les fds


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
	printf("In pipe mid for cmd %d, I should keep [%d][0] and [%d][1] open\n", idx + 1, idx - 1, idx);
	i = 0;
	close(fd[idx - 1][1]);
	printf("closed brother 1, going to close fd[%d][0]\n", idx);
	close(fd[idx][0]);
	printf("closed brothers\n");
	while (i < idx - 1)
	{
		printf("closing all fd[%d]\n", i);
		close(fd[i][1]);
		close(fd[i][0]);
		i++;		
	}
	i = cmd_nb - 2;
//	printf("mid mid\n");
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

int piping(t_data *data, int cmd_nb)
{
	int **fd;
	pid_t pid[cmd_nb];
	int j;
	int idx;

	fd = malloc(sizeof(int) * cmd_nb);
	idx = cmd_nb - 2;
	printf("%d fds\n", idx);

	while (idx >= 0)
	{
		fd[idx--] = malloc(sizeof(int) * 2);
	}
	idx = 0;
	while (idx < cmd_nb - 1)
	{
		if (pipe(fd[idx++]) < 0) //chié
		{
			return (1); // fermer tout ce qui est ouvert
		}
	}
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
		printf("gonna fork for cmd nb %d\n", idx + 1);
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
		printf("closing fds[%d][0]\n", idx);
		close(fd[idx][1]);
		printf("closing fds[%d][1]\n", idx);
		idx--;
	}
	idx = j;
	while (j <= idx)
	{
		printf("waiting for beautiful command number %d\n", idx);
		waitpid(pid[idx], NULL, 0);
		printf("done waiting for beautiful command number %d\n", idx);
//		j++;
		idx--;
	}
	printf("donzo mom\n");
	return (0);
}

//int		piping(t_data *data, int cmd_nb) //a+ grand mere
//{
//	int **fd;
	
//	pid = fork();
//	if (pid == 0)
//	{
//	piping_mother(data, cmd_nb, fd);
//	}
//	idx--;
	//while(idx >= 0)/
	//{
//		close(fd[idx][0]);
//		close(fd[idx][1]);
//		idx--;
//	}
//	waitpid(pid, NULL, 0);
/*	pid = waitpid(pid, &status, WUNTRACED); //waiting for a status change
		while (!WIFEXITED(status) && !WIFSIGNALED(status)) //while status is not exit or killed
		  pid = waitpid(pid, &status, WUNTRACED);*/

//	return (0);
//}
/*
int		builtouts2(t_data *data, t_commands cmd)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	printf("executing %s\n", cmd.fct.fct_path);
	pid = fork();
	if (pid == 0) 
	{		// Child process
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1) 
	  		return (0);
	} 
	else if (pid < 0)
		return (0);
	else
  	{     // Parent process
		wpid = waitpid(pid, &status, WUNTRACED); //waiting for a status change
		while (!WIFEXITED(status) && !WIFSIGNALED(status)) //while status is not exit or killed
		  wpid = waitpid(pid, &status, WUNTRACED);
  	}
	return (1);
}

int	ft_exec(t_data *data, int i)
{
	t_commands	cmd;

	cmd = data->cmds[i];
	if (cmd.fct.builtin)
	{
		if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
			data->is_exit = TRUE;
		if (!cmd.fct.builtin_ptr(cmd.args))
			return (0);
	}
	else
	{
		if (builtouts2(data, cmd) == 0)
			return (0);
	}
	return (0);
}

			





void	pipe_stdin(t_data *data, int *fd, int i)
{
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	printf("going to exec %s in pipe_stdin\n", data->cmds[i].args[0]);
	ft_exec(data, i);
//	execve(data->cmds[i].fct.fct_path, data->cmds[i].args, data->environ);
}

void	pipe_stdout(t_data *data, int *fd, int i)
{
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	printf("going to exec %s in pipe_stdout\n", data->cmds[i].args[0]);
	ft_exec(data, i);

//	execve(data->cmds[i].fct.fct_path, data->cmds[i].args, data->environ);
}

int		single_piping(t_data *data, int i)
{
	printf("single piping1\n");
	int	fds[2];
	pid_t	pid1;
	pid_t	pid2;
	printf("single piping2\n");
	if (pipe(fds) == -1) // a proteger
		printf("piping error in single\n");
	pid1 = fork(); //(a proteger)
	if (pid1 == -1)
		printf("forking1 error in single\n");
	if (pid1 == 0)
		pipe_stdin(data, fds, i);
	i++;
	pid2 = fork(); //a proteger
	if (pid2 == 0)
		pipe_stdout(data, fds, i);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("donzo\n");
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
//	i++;
	while (i-- != 0)
	{
		pipe (fds);
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

int	piping(t_data *data, int nb)
{
	int i;
	printf("in piping, nb = %d\n", nb);
	i = 0;
	if (nb == 2)
		single_piping(data, i);
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
*/