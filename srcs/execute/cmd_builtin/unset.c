/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/31 13:03:58 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static void	shift_all_env_var(char	***environ_var, int i, int size)
{
	char		**tmp_env;

	tmp_env = malloc(sizeof(char *) * size);
	while ((*environ_var)[i])
	{
		free((*environ_var)[i]);
		(*environ_var)[i] = NULL;
		if ((*environ_var)[i + 1] != NULL)
			(*environ_var)[i] = ft_strdup((*environ_var)[i + 1]);
		else
			break ;
		i++;
	}
}

int	builtin_unset(char **args, char ***environ_var)
{
	int			i;
	char		**split_env;
	int			found;
	int			size;

	found = 0;
	size = -1;
	while ((*environ_var)[++size])
		;
	i = -1;
	while ((*environ_var)[++i])
	{
		split_env = ft_split((*environ_var)[i], '=');
		if (ft_strncmp(args[1], split_env[0], \
		ft_strlen(split_env[0])) == 0)
		{
			found = 1;
			shift_all_env_var(environ_var, i, size);
			(*environ_var)[i] = NULL;
		}
		free_split(split_env);
	}
	if (!found)
		return (0);
	return (1);
}
