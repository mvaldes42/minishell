/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/12 14:20:04 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"

int	execute(t_data *data)
{
	int			i;
	t_commands	cmd;

	i = 0;
	while (i < data->pars.cmd_nbr)
	{
		cmd = data->cmds[i];
		if (cmd.fct.builtin)
			cmd.fct.builtin_ptr(cmd.args);
		i++;
	}
	return (1);
}
