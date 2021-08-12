/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:06:50 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/12 14:15:05 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../../minishell.h"

void	builtin_cd(char **args)
{
	char	*directory;

	if (args == NULL)
		directory = getenv("HOME");
	directory = args[0];
	// if (getenv("CDPATH") != NULL && directory[0] != '/')
	// use as a search path;
	if (chdir(directory) == 0)
	{
		printf("dir found\n");
	}
	else
	{
		errno = ENOENT;
		printf("dir not found\n");
	}
}
