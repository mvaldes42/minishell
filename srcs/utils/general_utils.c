/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 12:09:29 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

// extern char	**environ;
// int			i;

// i = -1;
// while (environ[++i] != NULL)
// 	ft_free(environ[i]);
// rl_clear_history();

void	exit_sucess(t_data *data, char *line)
{
	clear_data(data);
	ft_free(line);
	ft_putstr_fd("Sucess\n", STDERR);
	exit(EXIT_SUCCESS);
}

static void	free_tks(t_data *data)
{
	int	i;

	i = 0;
	if (data->pars.tks != NULL)
	{
		while (i < data->pars.tk_nbr)
		{
			ft_free(data->pars.tks[i].ptr);
			if (data->pars.tks[i].type == WEAK_WORD)
				ft_free(data->pars.tks[i].trans_weak);
			if (data->pars.tks[i].type == FUNCTION)
				ft_free(data->pars.tks[i].tk_fct_path);
			i++;
		}
		ft_free(data->pars.tks);
	}
}

void	clear_data(t_data *data)
{
	int	i;

	i = 0;
	free_tks(data);
	ft_free(data->prompt);
	while (i < data->pars.cmd_nbr && data->cmds)
	{
		ft_free(data->cmds[i].args);
		ft_free(data->cmds[i].redirs);
		i++;
	}
	ft_free(data->cmds);
	ft_memset(data, 0, sizeof(t_data));
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
