/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:44:04 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 11:26:22 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	builtin_echo(char **args)
{
	int		i;
	bool	opt;

	i = 0;
	opt = 0;
	if (args[1] && ft_strncmp(args[1], "-n", ft_strlen(args[1])) == 0)
	{
		i = 1;
		opt = TRUE;
	}
	while (args[++i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
	}
	if (opt == FALSE)
		printf("\n");
	return (1);
}
