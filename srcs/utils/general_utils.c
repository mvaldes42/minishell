/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/30 19:06:22 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	exit_fail(t_data *data)
{
	int	i;

	i = 0;
	if (data->s_tokens.tk_lst[i].token_ptr[0] != '\0')
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
	int	i;

	i = 0;
	if (data->s_tokens.tk_lst[i].token_ptr[0] != '\0')
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
	if (line)
		free(line);
	ft_putstr_fd("Sucess\n", STDERR);
	exit(EXIT_SUCCESS);
}

void	clear_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->s_tokens.tk_lst)
	{
		while (data->s_tokens.tk_lst[i].token_ptr && i < data->s_tokens.tk_nbr)
		{
			free(data->s_tokens.tk_lst[i].token_ptr);
			i++;
		}
		if (data->s_tokens.tk_lst)
			free(data->s_tokens.tk_lst);
	}
	ft_bzero(&data, sizeof(data));
}

void	print_prompt(void)
{
	char	cwd[256];

	ft_putstr_fd("-> ", STDOUT);
	ft_putstr_fd(getcwd(cwd, sizeof(cwd)), STDOUT);
	ft_putstr_fd(" >$ ", STDOUT);
}
