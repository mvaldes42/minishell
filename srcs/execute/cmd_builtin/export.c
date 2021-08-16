/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:33 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 13:47:43 by mvaldes          ###   ########.fr       */
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
	return (1);
}

static int	create_var(char **args)
{
	extern char	**environ;
	char		*p;
	int			size;

	p = NULL;
	size = 0;
	errno = 137;
	while (environ[size])
		size++;
	if (!is_name_valid(args[1]))
		return (0);
	p = malloc(sizeof(char *) * (size + 2));
	if (!p)
		return (0);
	memmove(p, *environ, size * sizeof(char *));
	environ[size] = ft_strdup(args[1]);
	environ[size + 1] = NULL;
	free(p);
	return (1);
}
// *environ = p;

int	builtin_export(char **args)
{
	extern char	**environ;
	int			i;
	char		*env_value;

	i = -1;
	if (args[1] == NULL)
		while (environ[++i])
			printf("declare -x %s\n", environ[i]);
	env_value = getenv(args[1]);
	if (env_value != NULL)
	{
		if (!reatribute_var(args, env_value))
			return (0);
	}
	else if (env_value == NULL)
		if (!create_var(args))
			return (0);
	return (1);
}
