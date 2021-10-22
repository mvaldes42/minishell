/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 14:23:22 by fcavillo         ###   ########.fr       */
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

static int	does_var_exists(int size, char *var_name, char ***environ_var)
{
	int		i;
	char	**split_env;

	i = -1;

	while (i < size - 1 && (*environ_var)[++i])
	{
		split_env = ft_split((*environ_var)[i], '=');
		if (ft_strncmp(var_name, split_env[0], \
		ft_strlen(split_env[0])) == 0)
		{
			free_split(&split_env);
			return (1);
		}
	}
	free_split(&split_env);	
	g_error = UNSET_NOT_FOUND;
	return (0);
}

static int	init_unset(char ***environ_var, char ***tmp_env, char *var_name, \
						int *size)
{
	int		i;

	*size = -1;
	while ((*environ_var)[++(*size)])
		;
	if (!does_var_exists(*size, var_name, environ_var))
		return (0);
	i = -1;
	g_error = ENOMEM;
	(*tmp_env) = malloc(sizeof(char *) * (*size + 1));
	if (!(*tmp_env))
		return (0);
	while ((*environ_var)[++i])
	{
		(*tmp_env)[i] = ft_strdup((*environ_var)[i]);
		ft_free_str(&(*environ_var)[i]);
	}
	ft_free_str(*environ_var);
	(*environ_var) = malloc(sizeof(char *) * *size);
	if (!(*environ_var))
		return (0);
	g_error = 0;
	return (1);
}

int	builtin_unset(char **args, int argc, char ***env)
{
	int			i;
	char		**split_env;
	int			size;
	char		**tmp_env;

	if (argc == 1)
		return (1);
	if (!is_name_valid_unset(args[1]) || \
	!init_unset(env, &tmp_env, args[1], &size))
		return (0);
	i = -1;
	while (i < size - 1 && tmp_env[++i])
	{
		split_env = ft_split(tmp_env[i], '=');
		if (ft_strncmp(args[1], split_env[0], ft_strlen(split_env[0])) == 0)
		{
			i = shift_all_env_var(env, tmp_env, i, size);
			free_split(&split_env);
			return (1);
		}
		(*env)[i] = ft_strdup(tmp_env[i]);
		ft_free_str(&tmp_env[i]);
		free_split(&split_env);
	}
	return (0);
}
