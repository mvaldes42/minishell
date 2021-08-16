/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:06:50 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 11:34:05 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../../minishell.h"

int	builtin_cd(char **args)
{
	char	*directory;
	int		i;

	i = 1;
	while (args[i] != NULL)
		i++;
	if (i == 1)
		directory = getenv("HOME");
	else
		directory = args[1];
	if (chdir(directory) == -1)
		return (0);
	return (1);
}

	// if (getenv("CDPATH") != NULL && directory[0] != '/')
	// use as a search path;