/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/19 11:14:00 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	free_tks(t_data *data)
{
	int	i;

	i = 0;
	if (data->pars.tks != NULL)
	{
		while (i < data->pars.tk_nbr)
		{
			ft_free_str(&data->pars.tks[i].ptr);
			ft_free_str(&data->pars.tks[i].modif_word);
			if (data->pars.tks[i].type == FUNCTION)
				ft_free_str(&data->pars.tks[i].tk_fct_path);
			i++;
		}
		free(data->pars.tks);
		data->pars.tks = NULL;
		ft_memset(data->pars.tks, 0, sizeof(data->pars.tks));
	}
}

void	clear_data(t_data *data)
{
	int	i;

	free_split(data->env_path);
	free_tks(data);
	ft_free_str(&data->prompt);
	i = -1;
	while (data->cmds && ++i < data->pars.cmd_nbr)
	{
		free(data->cmds[i].args);
		data->cmds[i].args = NULL;
		if (data->cmds[i].redirs)
		{
			free(data->cmds[i].redirs);
			data->cmds[i].redirs = NULL;
		}
	}
	if (data->pars.cmd_nbr)
	{
		ft_free_int(&data->pars.argv_size);
		free(data->cmds);
		data->cmds = NULL;
	}
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

void	free_environ(t_data *data)
{
	int	i;

	i = -1;
	if (data->environ != NULL)
	{
		while (data->environ[++i] != NULL)
		{
			free(data->environ[i]);
			data->environ[i] = NULL;
		}
	}
	free(data->environ);
	data->environ = NULL;
}

int	ft_str_in_str(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str2)) == 0)
		return (1);
	return (0);
}
