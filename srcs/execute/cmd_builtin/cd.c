/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:06:50 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/12 14:51:49 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../../minishell.h"

int	builtin_cd(char **args)
{
	char	*directory;
	int		i;

	i = 0;
	while (args[i] != NULL)
		i++;
	if (i == 0)
		directory = getenv("HOME");
	else
		directory = args[0];	
	// if (getenv("CDPATH") != NULL && directory[0] != '/')
	// use as a search path;
	if (chdir(directory) == -1)
		return (0);
	return (1);
}
