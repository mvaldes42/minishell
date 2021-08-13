/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 15:35:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/13 18:11:32 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"
#include "../execute/execute.h"

// echo -n bonjour|echo cool' $HOME top '" $HOME    super'$LANG' "
// echo " $HOME    super'$LANG' "
// ls -a > file1 > file2 >> file3

static int	get_redir_size(t_data *d, t_token *tks, int i)
{
	int	size;

	errno = ENOENT;
	size = 0;
	while (i < d->pars.tk_nbr && tks[i].type != PIPE)
	{
		if (!tks[i].redir)
			return (0);
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
	while (i < d->pars.tk_nbr && j < size)
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

	k = 0;
	cmd->args[k] = cmd->fct.name;
	while (++k < d->pars.argv_size[cmd->id] + 1 && ++i < d->pars.tk_nbr)
	{
		if (tks[i].type == WEAK_WORD)
			cmd->args[k] = tks[i].trans_weak;
		else if (tks[i].type == VARIABLE)
			cmd->args[k] = tks[i].trans_var;
		else
			cmd->args[k] = tks[i].ptr;
	}
	cmd->args[k] = NULL;
	return (i);
}

static void	input_cmd_fct_builtin(t_commands *cmd)
{
	if (ft_strncmp(cmd->fct.name, "echo", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_echo;
	else if (ft_strncmp(cmd->fct.name, "cd", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_cd;
	else if (ft_strncmp(cmd->fct.name, "pwd", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_pwd;
	else if (ft_strncmp(cmd->fct.name, "export", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_export;
	else if (ft_strncmp(cmd->fct.name, "unset", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_unset;
	else if (ft_strncmp(cmd->fct.name, "env", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_env;
	else if (ft_strncmp(cmd->fct.name, "exit", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_exit;
}

static int	input_command_fct(t_data *d, t_commands *cmd, t_token *tks, int i)
{
	cmd->fct.name = tks[i].ptr;
	if (tks[i].type == FUNCTION)
		cmd->fct.fct_path = tks[i].tk_fct_path;
	else if (tks[i].type == BUILTIN)
	{
		cmd->fct.builtin = 1;
		cmd->fct.name = tks[i].ptr;
		input_cmd_fct_builtin(cmd);
		if (!ft_strncmp(tks[i].ptr, "echo", 4) && tks[i].echo_opt)
		{
			cmd->echo_opt = 1;
			i++;
		}
	}
	i = cmd_args(d, cmd, tks, i);
	if (i + 1 < d->pars.tk_nbr && tks[i + 1].redir)
	{
		i += 1;
		i = cmd_redir_case(d, tks, cmd, i) + 1;
		if (i == 0)
			return (-1);
	}
	// if (i + 1 < d->pars.tk_nbr)
	// 	i += 1;
	return (i);
}

int	input_command_table(t_data *d)
{
	t_commands	*cmds;
	int			i;
	int			j;
	t_token		*tks;

	tks = d->pars.tks;
	d->cmds = malloc(sizeof(t_commands) * d->pars.cmd_nbr + 1);
	memset(d->cmds, 0, sizeof(t_commands));
	cmds = d->cmds;
	i = -1;
	j = -1;
	while (++j < d->pars.cmd_nbr && ++i < d->pars.tk_nbr)
	{
		printf("tks[i].ptr: %s\n", tks[i].ptr);
		memset(&cmds[j], 0, sizeof(t_commands));
		d->cmds[j].args = malloc(sizeof(char *) * (d->pars.argv_size[j] + 1));
		cmds[j].args = d->cmds[j].args;
		ft_memset(cmds[j].args, 0, sizeof(cmds[j].args));
		cmds[j].id = j;
		i = input_command_fct(d, &cmds[j], tks, i);
		if (i == -1)
			break ;
	}
	ft_free(d->pars.argv_size);
	if (i == -1)
		return (0);
	return (1);
}
