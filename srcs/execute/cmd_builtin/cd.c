/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:06:50 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/12 12:21:55 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../../minishell.h"

void	builtin_cd(char **args)
{
	if (chdir(args) == 0)
	{
		printf("dir found\n");
	}
	else
	{
		errno = ENOENT;
		printf("dir not found\n");
	}
}
