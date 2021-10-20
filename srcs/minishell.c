/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:34:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/20 14:50:30 by mvaldes          ###   ########.fr       */
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
	data->environ = malloc(sizeof(char *) * (size + 2));
	data->environ[0] = ft_strdup("?=0");
	i = 0;
	while (i < size)
	{
		data->environ[i + 1] = ft_strdup(environ[i]);
		i++;
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
	return (1);
}

static void	main_loop(t_data *data, char *line, int flag)
{
	bool	is_cmd_fail;
	int		is_exit;

	is_exit = 0;
	while (line)
	{
		is_cmd_fail = 0;
		if (!is_line_empty(line) || !parsing(data, line) || !navigate_line(data))
			is_cmd_fail = error_handling(data);
		else
		{
			ft_free_str(&data->environ[0]);
			data->environ[0] = ft_strdup("?=1");
		}
		if (data->is_exit)
			is_exit = 1;
		clear_data(data);
		if (!flag)
			ft_free_str(&line);
		else
			line = NULL;
		if (is_exit)
			break ;
		if (!flag)
		{
			create_prompt(data, is_cmd_fail);
			line = readline(data->prompt);
		}
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	char		*line;

	initialize_env(&data, &line);
	create_prompt(&data, 0);
	term();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		main_loop(&data, argv[2], 1);
		free_environ(&data);
		return (0);
	}
	line = readline(data.prompt);
	main_loop(&data, line, 0);
	rl_clear_history();
	free_environ(&data);
	return (0);
}
