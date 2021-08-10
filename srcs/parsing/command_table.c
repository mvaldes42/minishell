/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:35:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/10 15:11:46 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"

// echo -n bonjour|echo cool' $HOME top '" $HOME    super'$LANG' "
// echo " $HOME    super'$LANG' "
// ls -a > file1 > file2 >> file3

static int	get_redir_size(t_data *d, t_token *tks, int i)
{
	int	size;

	size = 0;
	while (i < d->prng.tk_nbr && tks[i].type != PIPE)
	{
		if (!tks[i].redir)
		{
			printf("redirection error\n");
			return (0);
		}
		i += 2;
		size++;
	}
	return (size);
}

static int	cmd_redir_case(t_data *d, t_token *tks, t_commands *cmd, int i)
{
	int	j;
	int	size;

	size = get_redir_size(d, tks, i);
	if (size == 0)
		return (-1);
	cmd->redirs = malloc(sizeof(t_redir_token) * (size + 1));
	ft_memset(cmd->redirs, 0, sizeof(cmd->redirs));
	j = 0;
	while (i < d->prng.tk_nbr && j < size)
	{
		i += 1;
		if (tks[i].type == WEAK_WORD)
			cmd->redirs[j].filename = tks[i].trans_weak;
		else if (tks[i].type == VARIABLE)
			cmd->redirs[j].filename = tks[i].trans_var;
		else
			cmd->redirs[j].filename = tks[i].ptr;
		j++;
		i += 1;
	}
	return (i);
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
	i = cmd_args(d, cmd, tks, i) + 1;
	if (tks[i].redir)
	{
		i = cmd_redir_case(d, tks, cmd, i) + 1;
		if (i == 0)
			return (-1);
	}
	return (i);
}

int	input_command_table(t_data *d)
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
		if (i == -1)
			break ;
	}
	free(d->prng.argv_size);
	if (i == -1)
		return (0);
	return (1);
}
