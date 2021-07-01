/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:03:21 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/01 20:01:24 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/utils.h"

// void	sigintHandler(int sig_num, char *line)
// {
// 	// signal(SIGINT, sigintHandler);
// 	printf("\n Cannot be terminated using Ctrl+C \n");
// 	// fflush(stdout);
// }

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data;
	char	*prompt;

	(void)argc;
	(void)argv;
	(void)env;
	line = NULL;
	ft_bzero(&data, sizeof(data));
	create_prompt(&prompt);
	line = readline(prompt);
	while (line)
	{
		add_history(line);
		// signal(SIGINT, void (*sigintHandler)());
		if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
			exit_sucess(&data, line);
		lexer(&data, line, &data.s_tokens);
		// printf("data: %s\n", data.s_tokens.tk_lst[0].token_ptr);
		clear_data(&data);
		if (line)
			free(line);
		line = readline(prompt);
		// printf("data: %s\n", data.s_tokens.tk_lst[0].token_ptr);
	}
	return (1);
}
