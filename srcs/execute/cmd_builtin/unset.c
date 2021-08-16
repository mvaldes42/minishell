/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 10:51:05 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		ft_free(split[i]);
	free(split);
}

int	builtin_unset(char **args)
{
	extern char	**environ;
	int			i;
	int			size;
	char		*p;
	char		**split;

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
		split = ft_split(environ[i], '=');
		if (ft_strncmp(split[0], args[1], ft_strlen(split[0])) == 0)
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
		free_split(split);
		i++;
	}
	environ[size] = NULL;
	return (1);
}
