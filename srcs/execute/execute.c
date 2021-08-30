/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/30 12:16:27 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"                                                                                                                                                                                                                                                                                        

//handle all errors

int	execute_one(t_data *data, int i)
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
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1)			
			return (0); //error to handle
	}
	return (0);
}

int	execute(t_data *data)
{
	pid_t		pid;
		
	if (data->pars.cmd_nbr >= 2)
	{
		piping(data, data->pars.cmd_nbr);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			execute_one(data, 0);
		waitpid(pid, NULL, 0);
	}
	return (1);
}
