/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/23 19:43:14 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	exit_fail(t_data *data)
{
	int	i;

	i = 0;
	if (data->s_tokens.tk_lst != NULL && \
	data->s_tokens.tk_lst[i].token_ptr[0] != '\0')
	{
		while (i < data->s_tokens.tk_nbr)
		{
			printf("free: \"%s.\"\n", data->s_tokens.tk_lst[i].token_ptr);
			free(data->s_tokens.tk_lst[i].token_ptr);
			i++;
		}
		if (data->s_tokens.tk_lst != NULL)
			free(data->s_tokens.tk_lst);
	}
	ft_putstr_fd("Error\n", STDERR);
	exit(EXIT_FAILURE);
}

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
		while (data->s_tokens.tk_lst[i].token_ptr && i < data->s_tokens.tk_nbr)
		{
			free(data->s_tokens.tk_lst[i].token_ptr);
			i++;
		}
		if (data->s_tokens.tk_lst)
			free(data->s_tokens.tk_lst);
	}
	if (data->prompt)
		free(data->prompt);
	ft_bzero(&data, sizeof(data));
}

void	create_prompt(t_data *data)
{
	char	cwd[256];
	int		size;

	size = ft_strlen(getcwd(cwd, sizeof(cwd))) + \
	ft_strlen("\033[32m\u27A1\033[0m \033[38;5;117;1m") + \
	ft_strlen(" \033[38;5;69m\u2613\033[0m ") + 1;
	data->prompt = (char *)malloc(sizeof(char) * size);
	strlcat(data->prompt, "\033[32m\u27A1\033[0m \033[38;5;117;1m", size);
	strlcat(data->prompt, getcwd(cwd, sizeof(cwd)), size);
	strlcat(data->prompt, " \033[38;5;69m\u2613\033[0m ", size);
}
