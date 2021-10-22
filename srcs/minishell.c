/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:34:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 11:42:36 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_env(t_data *data, char **line)
{
	extern char	**environ;
	int			i;
	int			size;

	ft_memset(data, 0, sizeof(t_data));
	data->is_exit = FALSE;
	data->prompt = NULL;
	line = NULL;
	size = -1;
	while (environ[++size])
		;
	data->environ = malloc(sizeof(char *) * (size + 1));
	i = -1;
	while (++i < size)
	{
		if (i == 0)
			data->environ[i] = ft_strdup("?=0");
		else if (i >= 1)
			data->environ[i] = ft_strdup(environ[i - 1]);
	}
	data->environ[size] = NULL;
}

static int	is_line_empty(char *line)
{
	if (char_occu(line, SPACE) == (int)ft_strlen(line))
	{
		errno = EMPTY_LINE;
		return (0);
	}
	add_history(line);
	g_error = 0;
	errno = 0;
	return (1);
}

static void	main_loop(t_data *d, char *line)
{
	bool	is_cmd_fail;
	int		is_exit;

	is_exit = 0;
	while (line)
	{
		is_cmd_fail = 0;
		if (!is_line_empty(line) || !parsing(d, line) || !navigate_line(d))
			is_cmd_fail = error_handling(d);
		else
		{
			ft_free_str(&d->environ[0]);
			d->environ[0] = ft_strdup("?=0");
		}
		if (d->is_exit)
			is_exit = 1;
		clear_data(d);
		ft_free_str(&line);
		if (is_exit)
			break ;
		handle_signals_empty();
		create_prompt(d, is_cmd_fail);
		line = readline(d->prompt);
	}
}

int	main(void)
{
	t_data		data;
	char		*line;

	initialize_env(&data, &line);
	create_prompt(&data, 0);
	handle_signals_empty();
	line = readline(data.prompt);
	main_loop(&data, line);
	free_environ(&data);
	ft_free_str(&data.prompt);
	rl_clear_history();
	return (g_error);
}
