/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/30 14:47:02 by mvaldes          ###   ########.fr       */
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
	if (data->s_tokens.tk_lst != NULL)
	{
		while (i < data->s_tokens.tk_nbr)
		{
			free(data->s_tokens.tk_lst[i].token_ptr);
			if (data->s_tokens.tk_lst[i].token_type == WEAK_WORD)
				free(data->s_tokens.tk_lst[i].trans_weak);
			i++;
		}
		free(data->s_tokens.tk_lst);
		data->s_tokens.tk_lst = NULL;
	}
	if (data->prompt)
		free(data->prompt);
	ft_memset(data, 0, sizeof(t_data));
}

void	create_prompt(t_data *data)
{
	char	cwd[256];
	int		size;

	size = ft_strlen(getcwd(cwd, sizeof(cwd))) + \
	ft_strlen("\u27A1 ") + \
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
