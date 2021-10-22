/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:19:44 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 11:06:00 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"

static int	is_args(t_token tk)
{
	if (tk.type != PIPE && tk.type != REDIR_IN && tk.type != \
		REDIR_OUT && tk.type != READ_IN && tk.type != REDIR_OUT_A)
		return (1);
	return (0);
}

static void	get_argv_size(t_data *data)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	data->pars.argv_size = malloc(sizeof(int) * (data->pars.cmd_nbr + 1));
	while (++i < data->pars.tk_nbr && j < data->pars.cmd_nbr)
	{
		data->pars.argv_size[j] = 1;
		if (data->pars.tks[i].type == FUNCTION || \
		data->pars.tks[i].type == BUILTIN)
		{
			i += 1;
			while (i < data->pars.tk_nbr && is_args(data->pars.tks[i]))
			{
				data->pars.argv_size[j] += 1;
				i++;
			}
			j += 1;
		}
	}
	data->pars.argv_size[j] = '\0';
}

static int	searcher(t_data *d)
{
	int			i;

	search_path_str(d);
	i = -1;
	while (++i < d->pars.tk_nbr)
	{
		if (d->pars.tks[i].redir || d->pars.tks[i].type == PIPE)
		{
			errno = UNEXPECTED_TK;
			if (i + 1 > d->pars.tk_nbr || d->pars.tks[i + 1].type != WORD)
				return (0);
			d->pars.tks[i].modif_word = ft_strdup(d->pars.tks[i].ptr);
		}
		else if (!expand_word(d, d->env_path, i))
			return (0);
		if (!remove_quotes(&d->pars.tks[i].modif_word))
			return (0);
	}
	return (1);
}

int	parsing(t_data *data, char *line)
{
	if (!lexer(data, line) || !searcher(data))
		return (0);
	get_argv_size(data);
	if (!input_command_table(data))
		return (0);
	return (1);
}
