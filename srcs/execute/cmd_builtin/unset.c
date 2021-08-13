/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/13 15:03:10 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	builtin_unset(char **args)
{
	extern char	**environ;
	int			i;
	int			size;
	char		*p;

	(void)args;
	size = 0;
	p = NULL;
	if (getenv(args[1]) == NULL)
		return (0);
	while (environ[size])
		size++;
	i = 0;
	while (i < size)
	{
		if (ft_strncmp(environ[i], args[1], ft_strlen(args[1])) == 0)
		{
			while (i < size)
			{
				free(environ[i]);
				environ[i] = NULL;
				if (i == size - 1)
					break ;
				else
					environ[i] = ft_strdup(environ[i + 1]);
				i++;
			}
		}
		i++;
	}
	environ[size] = NULL;
	return (1);
}
