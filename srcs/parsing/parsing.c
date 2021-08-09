/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:19:44 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/09 15:35:29 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"

static void	get_argv_size(t_data *data)
{
	int			i;
	int			j;
	t_token		*tk;

	i = 0;
	j = 0;
	data->prng.argv_size = malloc(sizeof(int) * data->prng.cmd_nbr + 1);
	while (i < data->prng.tk_nbr && j < data->prng.cmd_nbr)
	{
		tk = &data->prng.tks[i];
		data->prng.argv_size[j] = 0;
		if (tk->type == FUNCTION || tk->type == BUILTIN)
		{
			if (!ft_strncmp("echo", tk->ptr, ft_strlen("echo")) && i + 1 < data->prng.tk_nbr \
			&& !ft_strncmp("-n", data->prng.tks[i + 1].ptr, ft_strlen("-n")))
			{
				tk->echo_opt = 1;
				tk = &data->prng.tks[++i];
			}
			i += 1;
			tk = &data->prng.tks[i];
			while (tk->type != PIPE && tk->type != REDIR_IN && tk->type != \
			REDIR_OUT && tk->type != READ_IN && tk->type != REDIR_OUT_A \
			&& i <= data->prng.tk_nbr)
			{
				tk = &data->prng.tks[i];
				data->prng.argv_size[j] += 1;
				i++;
			}
			data->prng.argv_size[j] -= 1;
			i -= 1;
			j++;
		}
		i++;
	}
}

int	parsing(t_data *data, char *line)
{
	if (!lexer(data, line) || !searcher(data))
		return (0);
	print_parsing_tab(data);
	get_argv_size(data);
	input_command_table(data);
	print_cmd_tab(data);
	return (1);
}
