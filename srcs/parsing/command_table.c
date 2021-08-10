/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:35:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/10 11:24:03 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"

// echo -n bonjour|echo cool' $HOME top '" $HOME    super'$LANG' "
// echo " $HOME    super'$LANG' "

static void	cmd_redir_case(t_token *tk, t_commands *cmds)
{
	if (tk->type == REDIR_OUT)
		cmds->redirect_table.r_output = 1;
	if (tk->type == REDIR_OUT_A)
		cmds->redirect_table.r_app_output = 1;
	if (tk->type == REDIR_IN)
		cmds->redirect_table.r_input = 1;
	if (tk->type == READ_IN)
		cmds->redirect_table.read_input = 1;
}

static int	cmd_args(t_data *d, t_commands *cmd, t_token *tks, int i)
{
	int	k;

	k = -1;
	while (++k < d->prng.argv_size[cmd->id] && ++i < d->prng.tk_nbr)
	{
		if (tks[i].type == WEAK_WORD)
			cmd->args[k] = tks[i].trans_weak;
		else if (tks[i].type == VARIABLE)
			cmd->args[k] = tks[i].trans_var;
		else
			cmd->args[k] = tks[i].ptr;
	}
	return (i);
}

static int	input_command_fct(t_data *d, t_commands *cmd, t_token *tks, int i)
{
	cmd->fct.name = tks[i].ptr;
	if (tks[i].type == FUNCTION)
		cmd->fct.fct_path = tks[i].tk_fct_path;
	else if (tks[i].type == BUILTIN)
	{
		cmd->fct.builtin = 1;
		if (!ft_strncmp(tks[i].ptr, "echo", 4) && tks[i].echo_opt)
		{
			cmd->echo_opt = 1;
			i++;
		}
	}
	i = cmd_args(d, cmd, tks, i);
	if (tks[i].redir)
		cmd_redir_case(&tks[i], cmd);
	i++;
	return (i);
}

void	input_command_table(t_data *d)
{
	t_commands	*cmds;
	int			i;
	int			j;
	t_token		*tks;

	tks = d->prng.tks;
	d->cmds = malloc(sizeof(t_commands) * d->prng.cmd_nbr + 1);
	memset(d->cmds, 0, sizeof(t_commands));
	cmds = d->cmds;
	i = -1;
	j = -1;
	while (++j < d->prng.cmd_nbr && ++i < d->prng.tk_nbr)
	{
		memset(&cmds[j], 0, sizeof(t_commands));
		d->cmds[j].args = malloc(sizeof(char *) * (d->prng.argv_size[j] + 1));
		cmds[j].args = d->cmds[j].args;
		cmds[j].id = j;
		i = input_command_fct(d, &cmds[j], tks, i);
	}
	free(d->prng.argv_size);
}
