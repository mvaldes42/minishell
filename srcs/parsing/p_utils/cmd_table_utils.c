/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:58:50 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 15:01:52 by mvaldes          ###   ########.fr       */
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
		cmd->redirs[j].type = tks[i].type;
		i += 1;
		if (tks[i].type == WORD)
			cmd->redirs[j].filename = tks[i].modif_word;
		else
			cmd->redirs[j].filename = tks[i].ptr;
		j++;
		if (j < size)
			i += 1;
	}
	return (i);
}

int	cmd_args(t_data *d, t_commands *cmd, t_token *tks, int i)
{
	int		k;
	int		l;

	cmd->nbr_args = d->pars.argv_size[cmd->id];
	cmd->args[0] = cmd->fct.name;
	k = 1;
	while (k < d->pars.argv_size[cmd->id] && ++i < d->pars.tk_nbr)
	{
		l = -1;
		cmd->args[k++] = tks[i].modif_word;
	}
	cmd->args[d->pars.argv_size[cmd->id]] = NULL;
	return (i);
}

int	input_cmd_fct_builtin(t_commands *cmd)
{
	errno = 139;
	if (ft_strncmp(cmd->fct.name, "echo", ft_strlen(cmd->fct.name)) == 0 \
	|| ft_strncmp(cmd->fct.name, "ECHO", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_echo;
	else if (ft_strncmp(cmd->fct.name, "cd", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_cd;
	else if (ft_strncmp(cmd->fct.name, "pwd", ft_strlen(cmd->fct.name)) == 0 \
	|| ft_strncmp(cmd->fct.name, "PWD", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_pwd;
	else if (ft_strncmp(cmd->fct.name, "export", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_export;
	else if (ft_strncmp(cmd->fct.name, "unset", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_unset;
	else if (ft_strncmp(cmd->fct.name, "env", ft_strlen(cmd->fct.name)) == 0 \
	|| ft_strncmp(cmd->fct.name, "ENV", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_env;
	else if (ft_strncmp(cmd->fct.name, "exit", ft_strlen(cmd->fct.name)) == 0)
		cmd->fct.builtin_ptr = builtin_exit;
	if (cmd->fct.builtin_ptr == NULL)
		return (0);
	return (1);
}
