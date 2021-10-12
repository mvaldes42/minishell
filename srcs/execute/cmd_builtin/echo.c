/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:44:04 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 15:09:32 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	builtin_echo(char **args, int argc, char ***environ_var)
{
	int		i;
	bool	opt;

	(void)environ_var;
	i = 0;
	opt = 0;
	if (args[1] && ft_strncmp(args[1], "-n", ft_strlen(args[1])) == 0)
	{
		i = 1;
		opt = TRUE;
	}
	while (++i < argc)
	{
		if (args[i])
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
	}
	if (opt == FALSE)
		printf("\n");
	return (1);
}
