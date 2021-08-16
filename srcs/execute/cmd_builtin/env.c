/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:44 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 11:37:41 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include <stdio.h>

int	builtin_env(char **args)
{
	extern char	**environ;
	int			i;

	(void)args;
	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);
	return (1);
}
