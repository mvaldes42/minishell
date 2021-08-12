/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/12 16:31:33 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"

// returns 0 if there is a problem -> error handling
// 

int	execute(t_data *data)
{
	int			i;
	t_commands	cmd;

	i = 0;
	while (i < data->pars.cmd_nbr)
	{
		cmd = data->cmds[i];
		if (cmd.fct.builtin)
		{
			if (!cmd.fct.builtin_ptr(cmd.args))
				return (0);
		}
		else
			execve(cmd.fct.fct_path, cmd.args, data->environ);
		i++;
	}
	return (1);
}
