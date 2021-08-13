/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:33 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/13 16:57:45 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	builtin_export(char **args)
{
	extern char	**environ;
	int			size;
	char		*p;
	int			i;

	size = 0;
	p = NULL;
	i = -1;
	if (args[1] == NULL)
		while (environ[++i])
			printf("declare -x %s\n", environ[i]);
	else
	{
		while (environ[size])
			size++;
		p = malloc(sizeof(char *) * (size + 2));
		if (!p)
			return (0);
		memmove(p, *environ, size * sizeof(char *));
		// *environ = p;
		environ[size] = ft_strdup(args[1]);
		environ[size + 1] = NULL;
		free(p);
	}
	return (1);
}
