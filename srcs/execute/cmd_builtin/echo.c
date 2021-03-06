/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:44:04 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 09:39:59 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static int	is_opt(char **args, int argc, int *i)
{
	int	j;

	if (args[1] && ft_strncmp(args[1], "-n", ft_strlen("-n")) == 0)
	{
		while (*i < argc && ft_strncmp(args[*i], "-n", ft_strlen("-n")) == 0)
		{
			j = 1;
			while (j++ < (int)ft_strlen(args[*i]) - 1)
			{
				if (args[*i][j] != 'n')
					return (1);
			}
			(*i)++;
		}
		return (1);
	}
	return (0);
}

int	builtin_echo(char **args, int argc, char ***environ_var)
{
	int		i;
	bool	opt;

	(void)environ_var;
	i = 1;
	opt = is_opt(args, argc, &i);
	while (i < argc)
	{
		if (args[i] != NULL)
			ft_putstr_fd(args[i], 1);
		if (i + 1 < argc && args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (opt == FALSE)
		ft_putchar_fd('\n', 1);
	return (1);
}
