/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:34:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/05 11:34:13 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handdle_signals(void)
// {
// 	if (signal(SIGINT, handdle_ctrl_c) != SIG_ERR)
// 		;
// 	if (signal(SIGQUIT, handdle_ctrl_d) != SIG_ERR)
// 		;
// }

// void	handdle_ctrl_c(int nb)
// {
// 	printf("ctrl c");
// 	printf("\b\b");
// 	printf("\n");
// 	// g_data.line = "\0";
// 	loop();
// }

// void	handdle_ctrl_d(int nb)
// {
// 	printf("ctrl d");
// 	printf("\n");
// 	exit_sucess(&g_data, g_data.line);
// }

// void	loop(void)
// {
// 	// handdle_signals();
// 	add_history(g_data.line);
// 	if (ft_strncmp(g_data.line, "exit", ft_strlen("exit")) == 0)
// 		exit_sucess();
// 	lexer();
// 	// printf("data: %s\n", data.parsing.tk_lst[0].token_ptr);
// 	clear_data();
// 	if (g_data.line)
// 		ft_free_str(&g_data.line);
// 	g_data.line = readline(g_data.prompt);
// 	// printf("data: %s\n", data.parsing.tk_lst[0].token_ptr);
// }

static void	initialize_env(t_data *data, char **line)
{
	extern char	**environ;
	int			i;
	int			size;

	ft_memset(data, 0, sizeof(t_data));
	data->is_exit = FALSE;
	data->prompt = NULL;
	data->pid = NULL;
	line = NULL;
	size = -1;
	while (environ[++size])
		;
	data->environ = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		data->environ[i] = ft_strdup(environ[i]);
		i++;
	}
	data->environ[size] = NULL;
}

static int	is_line_empty(char *line)
{
	if (char_occu(line, SPACE) == (int)ft_strlen(line))
	{
		errno = 136;
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
		if (!is_line_empty(line) || !parsing(data, line) || \
		!execute(data))
			is_cmd_fail = error_handling();
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
