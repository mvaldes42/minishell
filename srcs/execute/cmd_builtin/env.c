/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:44 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/30 15:16:42 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include <stdio.h>

int	builtin_env(char **args, char **environ_var)
{
	int			i;

	(void)args;
	i = -1;
	while (environ_var[++i])
		printf("%s\n", environ_var[i]);
	return (1);
}
