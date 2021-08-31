/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:33 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/31 11:52:32 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

static char	*recreate_old_var(char **args, char *env_value)
{
	char		**split;
	char		*old_var;
	int			old_var_s;

	split = ft_split(args[1], '=');
	old_var_s = ft_strlen(env_value) + ft_strlen("=") + ft_strlen(split[0]) + 1;
	old_var = (char *)malloc(sizeof(char) * old_var_s);
	if (!old_var)
		return (0);
	ft_memset(old_var, 0, sizeof(old_var));
	ft_strlcat(old_var, split[0], old_var_s);
	ft_strlcat(old_var, "=", old_var_s);
	ft_strlcat(old_var, env_value, old_var_s);
	free_split(split);
	return (old_var);
}

static int	reatribute_var(char **args, char *env_value, char ***environ_var)
{
	char		*old_var;
	int			i;

	old_var = recreate_old_var(args, env_value);
	i = -1;
	while ((*environ_var)[++i])
	{
		if (ft_strncmp((*environ_var)[i], old_var, ft_strlen(old_var)) == 0)
		{
			free((*environ_var)[i]);
			(*environ_var)[i] = ft_strdup(args[1]);
		}
	}
	free(old_var);
	return (1);
}

static int	is_name_valid(char *str)
{
	int		i;
	char	**split;

	split = ft_split(str, '=');
	i = -1;
	while (split[0][++i])
	{
		if (!((split[0][i] >= 'A' && split[0][i] <= 'Z') || \
		(split[0][i] >= 'a' && split[0][i] <= 'z') || split[0][i] == '_'))
			return (0);
	}
	free_split(split);
	return (1);
}

static int	create_var(char **args, char ***environ_var)
{
	int			size;
	int			i;
	char		**tmp_environ;

	errno = 137;
	if (!is_name_valid(args[1]))
		return (0);
	size = 0;
	while ((*environ_var)[size])
		size++;
	tmp_environ = malloc(sizeof(char *) * (size + 2));
	if (!tmp_environ)
		return (0);
	i = -1;
	while (++i < size)
	{
		tmp_environ[i] = ft_strdup((*environ_var)[i]);
		free((*environ_var)[i]);
		(*environ_var)[i] = NULL;
	}
	tmp_environ[size] = ft_strdup(args[1]);
	tmp_environ[size + 1] = NULL;
	free(*environ_var);
	(*environ_var) = NULL;
	(*environ_var) = (char **)malloc(sizeof(char *) * (size + 2));
	if (!(*environ_var))
		return (0);
	i = -1;
	while (++i < size + 2)
	{
		(*environ_var)[i] = ft_strdup(tmp_environ[i]);
		ft_free_str(&tmp_environ[i]);
	}
	ft_free_str(tmp_environ);
	return (1);
}

int	builtin_export(char **args, char ***environ_var)
{
	int			i;
	char		*env_value;
	char		**split_env;
	char		**split_arg;

	i = -1;
	if (args[1] == NULL)
		while ((*environ_var)[++i])
			printf("declare -x %s\n", (*environ_var)[i]);
	else
	{
		i = -1;
		env_value = NULL;
		split_arg = ft_split(args[1], '=');
		while ((*environ_var)[++i])
		{
			split_env = ft_split((*environ_var)[i], '=');
			if (ft_strncmp(split_arg[0], split_env[0], \
			ft_strlen(split_env[0])) == 0)
				env_value = args[1];
			free_split(split_env);
		}
		free_split(split_arg);
		if (env_value != NULL)
			if (!reatribute_var(args, env_value, environ_var))
				return (0);
		if (env_value == NULL)
			if (!create_var(args, environ_var))
				return (0);
	}
	return (1);
}
