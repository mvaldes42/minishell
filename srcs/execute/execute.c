/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 15:24:59 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"

int	execute(t_data *data)
{
	int			i;
	t_commands	cmd;
	extern char	**environ;

	i = 0;
	while (i < data->pars.cmd_nbr)
	{
		cmd = data->cmds[i];
		if (cmd.fct.builtin)
		{
			if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
				data->is_exit = TRUE;
			if (!cmd.fct.builtin_ptr(cmd.args))
				return (0);
		}
		else
			execve(cmd.fct.fct_path, cmd.args, data->environ);
		i++;
	}
	return (1);
}
