/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/31 10:15:53 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static int	shift_all_env_var(char	**environ, int i, int size)
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
	return (i);
}

int	builtin_unset(char **args, char ***environ_var)
{
	int			i;
	int			size;
	char		*p;
	char		**split;

	size = 0;
	p = NULL;
	if (getenv(args[1]) == NULL)
		return (0);
	while (*environ_var[size])
		size++;
	i = 0;
	while (i < size)
	{
		split = ft_split(*environ_var[i], '=');
		if (split[0] != NULL && \
		ft_strncmp(split[0], args[1], ft_strlen(split[0])) == 0)
			i = shift_all_env_var(*environ_var, i, size);
		free_split(split);
		i++;
	}
	*environ_var[size] = NULL;
	return (1);
}
