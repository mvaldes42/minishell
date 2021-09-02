/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/02 15:31:53 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"
#include <fcntl.h>
#include <sys/stat.h>

// handle all errors
// EXIT que ce soit un builtin ou out + garder en memoire le code de sortie d'erreur
// EXIT SUCCESS et EXIT FAILURE

int	execute_fct(t_data *data)
{
	t_commands	cmd;
	pid_t		pid;
	
	cmd = data->cmds[0];
	if (cmd.fct.builtin)
	{
		if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
			data->is_exit = TRUE;
		if (!cmd.fct.builtin_ptr(cmd.args, &data->environ))
			return (0); // a preciser
	}
	else
	{
		pid = fork(); // a proteger
		if (pid == 0)
			if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)			
				return (0); //error to handle
		waitpid(pid, NULL, 0);
	}
	return (0); // a preciser
}

int	execute_piped_fct(t_data *data, int i)
{
	t_commands	cmd;
	
	cmd = data->cmds[i];
	if (cmd.fct.builtin)
	{
		if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
			data->is_exit = TRUE;
		if (!cmd.fct.builtin_ptr(cmd.args, &data->environ))
			return (0); // a preciser
	}
	else
	{
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)			
			return (0); //error to handle
	}
	exit (0); // a preciser
}

int	execute(t_data *data)
{
	int			pipe_nb;
	
	data->pid = malloc(sizeof(pid_t) * data->pars.cmd_nbr);
	pipe_nb = data->pars.cmd_nbr - 1;
	if (!data->pid)
		printf("malloc error\n");
	if (data->pars.cmd_nbr >= 2)
	{
		piping(data, data->pars.cmd_nbr);
		while (pipe_nb >= 0)
			waitpid(data->pid[pipe_nb--], NULL, 0);
	}
	else
	{
			execute_fct(data);  // gerer erreur
	}
	return (1);
}
