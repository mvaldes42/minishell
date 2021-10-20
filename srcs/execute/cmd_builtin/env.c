/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:44 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/20 12:41:42 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include <stdio.h>

int	builtin_env(char **args, int argc, char ***environ_var)
{
	int			i;

	(void)args;
	(void)argc;
	i = 0;
	while ((*environ_var)[++i] != NULL)
		printf("%s\n", (*environ_var)[i]);
	return (1);
}
