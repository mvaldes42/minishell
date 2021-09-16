/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:35:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/16 15:39:56 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"
#include "../execute/execute.h"

static int	input_command_fct(t_data *d, t_commands *cmd, t_token *tks, int i)
{
	errno = CMD_NOT_FOUND;
	cmd->fct.name = tks[i].modif_word;
	if (tks[i].type == FUNCTION)
		cmd->fct.fct_path = tks[i].tk_fct_path;
	else if (tks[i].type == BUILTIN)
	{
		cmd->fct.builtin = 1;
		if (!input_cmd_fct_builtin(cmd))
			return (-1);
	}
	i = cmd_args(d, cmd, tks, i);
	if (i + 1 < d->pars.tk_nbr && tks[i + 1].redir)
	{
		i += 1;
		i = cmd_redir_case(d, tks, cmd, i) + 1;
		if (i == 0)
			return (-1);
	}
	return (i + 1);
}

int	input_command_table(t_data *d)
{
	int			i;
	int			j;

	d->cmds = malloc(sizeof(t_commands) * d->pars.cmd_nbr + 1);
	memset(d->cmds, 0, sizeof(t_commands));
	i = -1;
	j = -1;
	while (++j < d->pars.cmd_nbr && ++i < d->pars.tk_nbr)
	{
		memset(&d->cmds[j], 0, sizeof(t_commands));
		d->cmds[j].args = malloc(sizeof(char *) * (d->pars.argv_size[j] + 1));
		ft_memset(d->cmds[j].args, 0, sizeof(d->cmds[j].args));
		d->cmds[j].id = j;
		i = input_command_fct(d, &d->cmds[j], d->pars.tks, i);
		if (i == -1)
			break ;
	}
	if (i == -1)
	{
		ft_free_int(&d->pars.argv_size);
		return (0);
	}
	return (1);
}
