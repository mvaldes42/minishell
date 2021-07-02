/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/02 15:58:42 by mvaldes          ###   ########.fr       */
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
	if (g_global.prompt)
		free(g_global.prompt);
	ft_bzero(&data, sizeof(data));
}

void	create_prompt(void)
{
	char	cwd[256];
	int		size;

	size = ft_strlen(getcwd(cwd, sizeof(cwd))) + \
	ft_strlen("-> ") + ft_strlen(" $> ") + 1;
	g_global.prompt = (char *)malloc(sizeof(char) * size);
	strlcat(g_global.prompt, "-> ", size);
	strlcat(g_global.prompt, getcwd(cwd, sizeof(cwd)), size);
	strlcat(g_global.prompt, " $> ", size);
}
