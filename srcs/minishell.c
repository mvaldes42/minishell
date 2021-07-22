/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:03:21 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/22 11:58:08 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/utils.h"

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
// 	// printf("data: %s\n", data.s_tokens.tk_lst[0].token_ptr);
// 	clear_data();
// 	if (g_data.line)
// 		free(g_data.line);
// 	g_data.line = readline(g_data.prompt);
// 	// printf("data: %s\n", data.s_tokens.tk_lst[0].token_ptr);
// }

static void	initialize_env(t_data *data, char **line, t_global *g_global)
{
	const char	*build_in[7] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	memcpy(g_global->build_in, build_in, sizeof(build_in));
	g_global->prompt = NULL;
	line = NULL;
	ft_bzero(&data, sizeof(data));
}

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	char		*line;

	initialize_env(&data, &line, &g_global);
	create_prompt();
	line = readline(g_global.prompt);
	while (line)
	{
		if (char_occu(line, CHAR_WHITESPACE) != ft_strlen(line))
			add_history(line);
		if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
			exit_sucess(&data, line);
		lexer(&data, line, &data.s_tokens);
		// printf("data: %s\n", data.s_tokens.tk_lst[0].token_ptr);
		clear_data(&data);
		if (line)
			free(line);
		create_prompt();
		line = readline(g_global.prompt);
		// printf("data: %s\n", data.s_tokens.tk_lst[0].token_ptr);
	}
	return (1);
}
