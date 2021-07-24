#include "minishell.h"
#include "utils/general_utils.h"

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

static void	initialize_env(t_data *data, char **line)
{
	ft_memset(data, 0, sizeof(t_data));
	data->prompt = NULL;
	line = NULL;
}

int	main(void)
{
	t_data		data;
	char		*line;

	initialize_env(&data, &line);
	create_prompt(&data);
	line = readline(data.prompt);
	while (line)
	{
		if (char_occu(line, CHAR_WHITESPACE) != (int)ft_strlen(line))
			add_history(line);
		if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
			exit_sucess(&data, line);
		lexer(&data, line, &data.s_tokens);
		// printf("data: %s\n", data.s_tokens.tk_lst[0].token_ptr);
		clear_data(&data);
		if (line)
			free(line);
		create_prompt(&data);
		line = readline(data.prompt);
		// printf("data: %s\n", data.s_tokens.tk_lst[0].token_ptr);
	}
	return (1);
}
