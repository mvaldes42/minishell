/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/02 11:48:14 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

static void	free_tks(t_data *data)
{
	int	i;

	i = 0;
	if (data->pars.tks != NULL)
	{
		while (i < data->pars.tk_nbr)
		{
			ft_free_str(&data->pars.tks[i].ptr);
			if (data->pars.tks[i].type == WEAK_WORD)
				ft_free_str(&data->pars.tks[i].trans_weak);
			if (data->pars.tks[i].type == FUNCTION)
				ft_free_str(&data->pars.tks[i].tk_fct_path);
			i++;
		}
		free(data->pars.tks);
		ft_memset(data->pars.tks, 0, sizeof(data->pars.tks));
	}
}

void	clear_data(t_data *data)
{
	int	i;

	free_tks(data);
	ft_free_str(&data->prompt);
	i = -1;
	while (++i < data->pars.cmd_nbr && data->cmds)
		free(data->cmds[i].redirs);
	if (data->pars.cmd_nbr)
		free(data->cmds);
	ft_memset(&data->pars, 0, sizeof(t_parsing));
	ft_memset(data->cmds, 0, sizeof(t_commands));
	data->is_exit = 0;
	errno = 0;
}

int	char_occu(char *str, char c)
{
	int		nbr;
	char	*s;

	s = str;
	nbr = 0;
	while (*s)
	{
		if (*s == c)
			nbr++;
		s++;
	}
	if (nbr > 0)
		return (nbr);
	return (0);
}
