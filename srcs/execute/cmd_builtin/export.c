/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:33 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/30 17:44:23 by mvaldes          ###   ########.fr       */
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

static int	reatribute_var(char **args, char *env_value)
{
	extern char	**environ;
	char		*old_var;
	int			i;

	old_var = recreate_old_var(args, env_value);
	i = -1;
	while (environ[++i])
	{
		if (ft_strncmp(environ[i], old_var, ft_strlen(old_var)) == 0)
		{
			free(environ[i]);
			environ[i] = ft_strdup(args[1]);
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
	while (*environ_var[size])
		size++;
	tmp_environ = malloc(sizeof(char *) * (size + 2));
	if (!tmp_environ)
		return (0);
	i = -1;
	while (*environ_var[++i])
	{
		tmp_environ[i] = ft_strdup(*environ_var[i]);
		ft_free(*environ_var[i]);
	}
	tmp_environ[size] = ft_strdup(args[1]);
	tmp_environ[size + 1] = NULL;
	ft_free(*environ_var);
	*environ_var = malloc(sizeof(char *) * (size + 2));
	if (!*environ_var)
		return (0);
	i = -1;
	while (tmp_environ[++i])
	{
		*environ_var[i] = ft_strdup(tmp_environ[i]);
		ft_free(tmp_environ[i]);
	}
	ft_free(tmp_environ);
	return (1);
}

int	builtin_export(char **args, char ***environ_var)
{
	int			i;
//	char		*env_value;

	i = -1;
	printf("%s\n", *environ_var[0]);
	(void)args;
	// env_value = NULL;
	// if (args[1] == NULL)
	// 	while (*environ_var[++i])
	// 		printf("declare -x %s\n", *environ_var[i]);
	// i = -1;
	// while (*environ_var[++i])
	// {
	// 	if (ft_strncmp(args[1], *environ_var[i], ft_strlen(*environ_var[i])) == 0)
	// 		env_value = *environ_var[i];
	// }
	// if (env_value != NULL)
	// {
	// 	if (!reatribute_var(args, env_value))
	// 		return (0);
	// }
	// else if (env_value == NULL)
	// 	if (!create_var(args, environ_var))
	// 		return (0);
	return (1);
}
