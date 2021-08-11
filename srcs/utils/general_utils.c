/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/11 14:45:56 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	ft_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	error_handling(void)
{
	static char	*errors[] = {"missing quote", "", "command not found", \
	"syntax error near unexpected token"};
	int			i;

	if (errno > 131)
	{
		i = errno - 131 - 1;
		if (i == 1)
			printf("%s\n", errors[i]);
		else
			printf("minishell: %s\n", errors[i]);
	}
	else
		printf("minishell: %s\n", strerror(errno));
}

void	exit_sucess(t_data *data, char *line)
{
	clear_data(data);
	ft_free(line);
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

void	create_prompt(t_data *data)
{
	char	cwd[256];
	int		size;
	char	*arrow;
	char	*cross;

	arrow = "\033[32m\u27A1\033[0m \033[48;5;57m";
	cross = "\033[0m \033[38;5;69m\u2613\033[0m ";
	getcwd(cwd, sizeof(cwd));
	size = ft_strlen(cwd) + ft_strlen(arrow) + ft_strlen(cross) + 1;
	data->prompt = (char *)malloc(sizeof(char) * size);
	ft_memset(data->prompt, 0, sizeof(data->prompt));
	ft_strlcat(data->prompt, arrow, size);
	ft_strlcat(data->prompt, cwd, size);
	ft_strlcat(data->prompt, cross, size);
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
