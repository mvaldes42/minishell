/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:58:50 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 12:05:37 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"
#include "parsing_utils.h"

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

int	cmd_redir_case(t_data *d, t_token *tks, t_commands *cmd, int i)
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

int	cmd_args(t_data *d, t_commands *cmd, t_token *tks, int i)
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

void	input_cmd_fct_builtin(t_commands *cmd)
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
