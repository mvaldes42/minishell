/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 14:28:09 by fcavillo          #+#    #+#             */
/*   Updated: 2021/09/23 18:41:32 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// open non existant dir -> error ?
// la redir est excutee en premier, que les autres commandes existent ou pas
// la redir doit etre placee avant l'arrivee a exec
// execute_fct ??by adding i in the parameters, 0 single use, i multi command

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
		fd = open(cmd.redirs->filename, O_RDONLY,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); //check errors
		dup2(fd, STDIN_FILENO);
		close(fd);
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)
			return (0); //error to handle
		exit (0); //error to handle
	}
	close(fd);
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
		fd = open(cmd.redirs->filename, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); //check errors
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)
			return (0); //error to handle
		exit (0); //error to handle
	}
	close(fd);
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
		fd = open(cmd.redirs->filename, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR); //check errors
		dup2(fd, STDOUT_FILENO);
		close(fd);
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)
			return (0); //error to handle
		exit (0); //error to handle
	}
	// close(fd);
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
	return (1);
}

int	check_redir(t_data *data)
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
		return (-1);
	return (0);
}
