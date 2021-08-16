/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:19:44 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 11:30:35 by mvaldes          ###   ########.fr       */
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
	data->pars.argv_size = malloc(sizeof(int) * data->pars.cmd_nbr + 1);
	while (++i < data->pars.tk_nbr && j < data->pars.cmd_nbr)
	{
		data->pars.argv_size[j] = 1;
		if (data->pars.tks[i].type == FUNCTION || \
		data->pars.tks[i].type == BUILTIN)
		{
			while (is_args(data->pars.tks[++i]) && i < data->pars.tk_nbr)
				data->pars.argv_size[j] += 1;
			i -= 1;
			j += 1;
		}
	}
}

int	parsing(t_data *data, char *line)
{
	if (!lexer(data, line) || !searcher(data))
		return (0);
	print_parsing_tab(data);
	get_argv_size(data);
	if (!input_command_table(data))
		return (0);
	print_cmd_tab(data);
	return (1);
}
