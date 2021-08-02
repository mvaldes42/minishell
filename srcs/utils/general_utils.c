/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/02 14:34:17 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	exit_sucess(t_data *data, char *line)
{
	clear_data(data);
	if (line)
		free(line);
	ft_putstr_fd("Sucess\n", STDERR);
	exit(EXIT_SUCCESS);
}

void	clear_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->prng.tks != NULL)
	{
		while (i < data->prng.tk_nbr)
		{
			free(data->prng.tks[i].ptr);
			if (data->prng.tks[i].type == WEAK_WORD)
				free(data->prng.tks[i].trans_weak);
			i++;
		}
		free(data->prng.tks);
		data->prng.tks = NULL;
	}
	if (data->prompt)
		free(data->prompt);
	ft_memset(data, 0, sizeof(t_data));
}

void	create_prompt(t_data *data)
{
	char	cwd[256];
	int		size;

	size = ft_strlen(getcwd(cwd, sizeof(cwd))) + ft_strlen("\u27A1 ") + \
	ft_strlen(" \u2613 ");
	data->prompt = (char *)malloc(sizeof(char) * (size + 1));
	strcat(data->prompt, "\u27A1 ");
	strcat(data->prompt, getcwd(cwd, sizeof(cwd)));
	strcat(data->prompt, " \u2613 ");
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
