/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:28:09 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/05 12:00:20 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
// open non existant dir -> error ?
// la redir est excutee en premier, que les autres commandes existent ou pas
// la redir doit etre placee avant l'arrivee a exec
// execute_fct ?? by adding i in the parameters, 0 single use, i multi command
*/

//v2


void	redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); //check errors
	if (fd == -1)
		return;  //error
	dup2(fd, STDIN_FILENO);
	close(fd);
}

void	redir_append_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); //check errors
	if (fd == -1)
		return;  //error
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); //check errors
	if (fd == -1)
		return;  //error
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	handle_redirs(t_data *data, int type, char *filename, int *initial_fd)
{
	if (type == REDIR_OUT) // >
		redir_out(filename);
	else if (type == REDIR_OUT_A) // >>
		redir_append_out(filename);
	else if (type == REDIR_IN) // <
		redir_in(filename);
//	else if (type == READ_IN) // <<	
//		exec_read_in(data, i);
	(void)data;
	(void)initial_fd; //to use in heredoc
}

void	make_redirects(t_data *data, int base_rank, int rank, int *initial_fd) //checkredirs
{
	int	i;
	int	j;
	int type;
	char *filename;
//	printf("in make_redirects, base_rank = %d, rank = %d\n", base_rank, rank);
	
	i = base_rank;
	while (i <= rank)
	{
		if (data->cmds[i].redirs)  //JUST FIND A BETTER WAY
		{
			j = 0;
			printf("in make_redirects while, j = %d\n", j);

			type = 0;
			type = data->cmds[i].redirs[j].type;
			filename = data->cmds[i].redirs[j].filename;
			while (type >= 0 && type <= 6)//(data->cmds[i].redirs[j])
			{
				handle_redirs(data, type, filename, initial_fd);
				j++;
				type = data->cmds[i].redirs[j].type;
				filename = data->cmds[i].redirs[j].filename;
			}
		}
		i++;
	}
}

//v1
/*
int	exec_redir_in(t_data *data, int i)
{
	int			pid;
	int			fd;
	t_commands	cmd;

	cmd = data->cmds[i];
	fd = 0;
	pid = fork(); //a proteger
	if (pid == 0)
	{
		fd = open(cmd.redirs[0].filename, O_RDONLY,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); //check errors
		dup2(fd, STDIN_FILENO);
		close(fd);
		
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)
			return (0); //error to handle
		exit (0); //error to handle
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	exec_append_redir_out(t_data *data, int i)
{
	int			pid;
	int			fd;
	t_commands	cmd;

	cmd = data->cmds[i];
	fd = 0;
	pid = fork(); //a proteger
	if (pid == 0)
	{
		fd = open(cmd.redirs[0].filename, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); //check errors
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)
			return (0); //error to handle
		exit (0); //error to handle
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	exec_redir_out(t_data *data, int i)
{
	int			pid;
	int			fd;
	t_commands	cmd;

	cmd = data->cmds[i];
	fd = 0;
	pid = fork(); //a proteger
	if (pid == 0)
	{
		fd = open(cmd.redirs[0].filename, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); //check errors
		dup2(fd, STDOUT_FILENO);
		close(fd);
		execute_fct(data);
//		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)
//			return (0); //error to handle
		exit (0); //error to handle
	}
	waitpid(pid, NULL, 0);
	return (0);
}

int	handle_redir(t_data *data, int type, int i)
{
	if (type == REDIR_OUT) // >
		exec_redir_out(data, i);
	else if (type == REDIR_OUT_A) // >>
		exec_append_redir_out(data, i);
	else if (type == REDIR_IN) // <
		exec_redir_in(data, i);
	else if (type == READ_IN) // <<	
		exec_read_in(data, i);
	return (0);
}

int	check_redir(t_data *data) //so here it should send each redir separately, cmd by cmd
{
	int	i;
	int	type;
	int	has;

	has = 0;
	i = 0;
	while (i < data->pars.cmd_nbr)
	{
		if (data->cmds[i].redirs)
		{
			type = data->cmds[i].redirs[0].type;
			printf("type = %d\n", type);
			handle_redir(data, type, i);
			has++;
		}
		i++;
	}
	if (has)
		return (1);
	return (0);
}
*/