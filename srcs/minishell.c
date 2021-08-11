/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 16:34:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/11 18:39:17 by mvaldes          ###   ########.fr       */
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
// 		ft_free(g_data.line);
// 	g_data.line = readline(g_data.prompt);
// 	// printf("data: %s\n", data.parsing.tk_lst[0].token_ptr);
// }

static void	initialize_env(t_data *data, char **line)
{
	extern char	**environ;

	ft_memset(data, 0, sizeof(t_data));
	data->prompt = NULL;
	line = NULL;
	(void)line;
	data->environ = environ;
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

static void	main_loop(t_data *data, char *line)
{
	bool	is_cmd_fail;

	while (line)
	{
		is_cmd_fail = 0;
		if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
			exit_sucess(data, line);
		if (!is_line_empty(line) || !parsing(data, line))
			is_cmd_fail = error_handling();
		clear_data(data);
		ft_free(line);
		if (is_cmd_fail)
			create_prompt_fail(data);
		else
			create_prompt(data);
		line = readline(data->prompt);
	}
}

int	main(void)
{
	t_data		data;
	char		*line;

	initialize_env(&data, &line);
	create_prompt(&data);
	line = readline(data.prompt);
	main_loop(&data, line);
	return (0);
}
