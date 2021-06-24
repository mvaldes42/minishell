/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:03:21 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/24 17:03:55 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_prompt(void)
{
	char	cwd[256];

	ft_putstr_fd("-> ", STDOUT);
	ft_putstr_fd(getcwd(cwd, sizeof(cwd)), STDOUT);
	ft_putstr_fd(" >$ ", STDOUT);
}

int	lexer(char *line, t_data *data)
{
	(void)line;
	(void)data;
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_data			data;

	(void)argc;
	(void)argv;
	(void)env;
	line = NULL;
	// data.s_tokens->tokens_lst->token_type = CHAR_SINGLE_QUOTE;
	// printf("%c\n", data.s_tokens->tokens_lst->token_type);
	print_prompt();
	while (get_next_line(STDIN, &line) > 0)
	{
		lexer(line, &data);
		print_prompt();
	}
	return (1);
}
