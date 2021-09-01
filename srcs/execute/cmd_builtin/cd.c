/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:06:50 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/01 13:54:11 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../../minishell.h"

int	builtin_cd(char **args, char ***environ_var)
{
	char	*directory;
	int		i;

	i = 1;
	while (args[i] != NULL)
		i++;
	if (i == 1)
	{
		errno = 138;
		directory = ft_getenv("HOME", *environ_var);
		if (directory == NULL)
			return (0);
	}
	else
		directory = args[1];
	if (chdir(directory) == -1)
		return (0);
	return (1);
}
