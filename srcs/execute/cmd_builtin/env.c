/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:44 by mvaldes           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/08/12 14:27:48 by mvaldes          ###   ########.fr       */
=======
/*   Updated: 2021/08/12 16:07:22 by mvaldes          ###   ########.fr       */
>>>>>>> mlv/builtins
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include <stdio.h>

int	builtin_env(char **args)
{
<<<<<<< HEAD
	(void)args;
=======
	extern char	**environ;
	int			i;

	(void)args;
	i = -1;
	while (environ[++i])
		printf("%s\n", environ[i]);
>>>>>>> mlv/builtins
	return (1);
}
