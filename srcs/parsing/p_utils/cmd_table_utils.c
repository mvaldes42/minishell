/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_table_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:58:50 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/06 18:10:51 by mvaldes          ###   ########.fr       */
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
		i += 1;
	}
	return (i);
}

int	cmd_args(t_data *d, t_commands *cmd, t_token *tks, int i)
{
	int		k;
	int		l;
	char	**args_split;
	int		tk_count;

	cmd->args[0] = cmd->fct.name;
	k = 1;
	while (k < d->pars.argv_size[cmd->id] && ++i < d->pars.tk_nbr)
	{
		l = -1;
		tk_count = token_count(tks[i].modif_word);
		if (tk_count > 1)
		{	
			args_split = token_split(tks[i].modif_word, tk_count);
			while (args_split[++l] && k < d->pars.argv_size[cmd->id])
				cmd->args[k++] = ft_strdup(args_split[l]);
			free_split(args_split);
		}
		else
			cmd->args[k++] = tks[i].modif_word;
	}
	cmd->args[d->pars.argv_size[cmd->id]] = NULL;
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
