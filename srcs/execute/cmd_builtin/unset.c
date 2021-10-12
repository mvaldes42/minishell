/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 18:47:50 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static int	shift_all_env_var(char	***env_var, char **tmp_env, int i, int size)
{
	ft_free_str(&tmp_env[i]);
	while (i < size - 1)
	{
		(*env_var)[i] = ft_strdup(tmp_env[i + 1]);
		ft_free_str(&tmp_env[i + 1]);
		i++;
	}
	(*env_var)[i] = NULL;
	return (i);
}

static void	init_unset(char ***environ_var, char ***tmp_env, int *size)
{
	int		i;

	i = -1;
	(*size) = -1;
	while ((*environ_var)[++(*size)])
		;
	(*tmp_env) = malloc(sizeof(char *) * (*size + 1));
	while ((*environ_var)[++i])
	{
		(*tmp_env)[i] = ft_strdup((*environ_var)[i]);
		ft_free_str(&(*environ_var)[i]);
	}
	ft_free_str(*environ_var);
	(*environ_var) = malloc(sizeof(char *) * *size);
}

int	builtin_unset(char **args, int argc, char ***environ_var)
{
	int			i;
	char		**split_env;
	int			size;
	char		**tmp_env;

	(void)argc;
	init_unset(environ_var, &tmp_env, &size);
	i = -1;
	while (i < size - 1 && tmp_env[++i])
	{
		split_env = ft_split(tmp_env[i], '=');
		if (ft_strncmp(args[1], split_env[0], \
		ft_strlen(split_env[0])) == 0)
		{
			i = shift_all_env_var(environ_var, tmp_env, i, size);
			free_split(split_env);
			return (1);
		}
		(*environ_var)[i] = ft_strdup(tmp_env[i]);
		ft_free_str(&tmp_env[i]);
		free_split(split_env);
	}
	return (0);
}
