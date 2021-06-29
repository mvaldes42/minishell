/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:03:21 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/29 19:45:22 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_data			data;

	(void)argc;
	(void)argv;
	(void)env;
	line = NULL;
	ft_bzero(&data, sizeof(data));
	print_prompt();
	while (get_next_line(STDIN, &line) > 0)
	{
		lexer(line, &data.s_tokens);
		print_prompt();
	}
	return (1);
}
