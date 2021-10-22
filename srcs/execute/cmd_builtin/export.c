/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:33 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 11:51:27 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static int	reatribute_var(char **args, char ***env_var, char *old_var)
{
	int			i;

	i = -1;
	while ((*env_var)[++i])
	{
		if (ft_strncmp((*env_var)[i], old_var, ft_strlen(old_var)) == 0)
		{
			ft_free_str(&(*env_var)[i]);
			(*env_var)[i] = ft_strdup(args[1]);
		}
	}
	return (1);
}

static	int	init_create_var(char **args, char ***env_var, char ***tmp_env, \
			int *size)
{
	int	i;

	if (!is_name_valid(args[1]))
		return (0);
	while ((*env_var)[*size])
		(*size)++;
	*tmp_env = malloc(sizeof(char *) * (*size + 2));
	if (!(*tmp_env))
	{
		g_error = errno;
		return (0);
	}
	i = -1;
	while (++i < *size)
	{
		(*tmp_env)[i] = ft_strdup((*env_var)[i]);
		ft_free_str(&(*env_var)[i]);
		(*env_var)[i] = NULL;
	}
	(*tmp_env)[*size] = ft_strdup(args[1]);
	(*tmp_env)[*size + 1] = NULL;
	ft_free_str(*env_var);
	(*env_var) = NULL;
	return (1);
}

static int	create_var(char **args, char ***env_var)
{
	int			size;
	int			i;
	char		**tmp_env;

	size = 0;
	if (!init_create_var(args, env_var, &tmp_env, &size))
		return (0);
	(*env_var) = (char **)malloc(sizeof(char *) * (size + 2));
	if (!(*env_var))
	{
		g_error = errno;
		return (0);
	}
	i = -1;
	while (++i < size + 2)
	{
		(*env_var)[i] = ft_strdup(tmp_env[i]);
		ft_free_str(&tmp_env[i]);
	}
	ft_free_str(tmp_env);
	return (1);
}

static int	does_var_exists(char **args, char ***env_var, char **env_value)
{
	char		**split_arg;
	char		**split_env;
	int			i;
	int			r_value;

	r_value = 1;
	split_arg = ft_split(args[1], '=');
	if (split_arg[0] == NULL)
		r_value = 0;
	else
	{
		i = -1;
		while ((*env_var)[++i])
		{
			split_env = ft_split((*env_var)[i], '=');
			if (ft_strncmp(split_arg[0], split_env[0], \
			ft_strlen(split_env[0])) == 0)
				*env_value = (*env_var)[i];
			free_split(&split_env);
		}
	}
	free_split(&split_arg);
	return (r_value);
}

int	builtin_export(char **args, int argc, char ***env_var)
{
	int			i;
	char		*env_value;

	(void)argc;
	i = -1;
	if (args[1] == NULL)
		while ((*env_var)[++i])
			printf("declare -x %s\n", (*env_var)[i]);
	else
	{
		env_value = NULL;
		if (!does_var_exists(args, env_var, &env_value))
			return (0);
		if (env_value != NULL && !reatribute_var(args, env_var, env_value))
			return (0);
		else if (env_value == NULL && !create_var(args, env_var))
			return (0);
	}
	return (1);
}
