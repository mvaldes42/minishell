/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 18:03:21 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/22 19:28:45 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	cwd[256];

	(void)argc;
	(void)argv;
	(void)env;
	line = NULL;
	printf("%s >$ ", getcwd(cwd, sizeof(cwd)));
	while (get_next_line(STDIN, &line) > 0)
	{
	// 	printf("line : %s\n", line);
	// 	printf("%s >$ ", getcwd(cwd, sizeof(cwd)));
	}
	return (1);
}
