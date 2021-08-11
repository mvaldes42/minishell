/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/11 12:57:01 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	error_handling(void)
{
	static char	*errors[] = {"missing quote", "", "command not found", \
	"syntax error near unexpected token"};
	int			i;

	if (errno > 131)
	{
		i = errno - 131 - 1;
		printf("minishell: %s\n", errors[i]);
	}
	else
		printf("minishell: %s\n", strerror(errno));
}

void	exit_sucess(t_data *data, char *line)
{
	clear_data(data);
	if (line)
		free(line);
	ft_putstr_fd("Sucess\n", STDERR);
	exit(EXIT_SUCCESS);
}

void	free_tks(t_data *data)
{
	int	i;

	i = 0;
	if (data->pars.tks != NULL)
	{
		while (i < data->pars.tk_nbr)
		{
			free(data->pars.tks[i].ptr);
			if (data->pars.tks[i].type == WEAK_WORD)
				free(data->pars.tks[i].trans_weak);
			if (data->pars.tks[i].type == FUNCTION)
				free(data->pars.tks[i].tk_fct_path);
			i++;
		}
		free(data->pars.tks);
		data->pars.tks = NULL;
	}
}

void	clear_data(t_data *data)
{
	int	i;

	i = 0;
	free_tks(data);
	if (data->prompt != NULL)
		free(data->prompt);
	while (i < data->pars.cmd_nbr && data->cmds)
	{
		free(data->cmds[i].args);
		if (data->cmds[i].redirs != NULL)
			free(data->cmds[i].redirs);
		i++;
	}
	if (data->cmds != NULL)
		free(data->cmds);
	ft_memset(data, 0, sizeof(t_data));
	errno = 0;
}

void	create_prompt(t_data *data)
{
	char	cwd[256];
	int		size;

	getcwd(cwd, sizeof(cwd));
	size = ft_strlen(cwd) + ft_strlen("\u27A1 ") + \
	ft_strlen(" \u2613 ") + 1;
	data->prompt = (char *)malloc(sizeof(char) * size);
	ft_memset(data->prompt, 0, sizeof(data->prompt));
	ft_strlcat(data->prompt, "\u27A1 ", size);
	ft_strlcat(data->prompt, cwd, size);
	ft_strlcat(data->prompt, " \u2613 ", size);
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
