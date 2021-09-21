/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:06:50 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/21 12:15:37 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../../minishell.h"

static int	export_var_path(char *var_name, char *path, char ***environ_var)
{
	char	*pwd;
	int		size;
	char	*args[2];

	size = ft_strlen(path) + ft_strlen(var_name) + 1;
	pwd = (char *)malloc(sizeof(char) * size);
	if (!pwd)
		return (0);
	ft_memset(pwd, 0, sizeof(pwd));
	ft_strlcat(pwd, var_name, size);
	ft_strlcat(pwd, path, size);
	args[0] = "export";
	args[1] = pwd;
	if (!builtin_export(args, environ_var))
	{
		ft_free_str(&pwd);
		return (0);
	}
	ft_free_str(&pwd);
	return (1);
}

static int	export_pwd_vars(char *old_cwd, char ***environ_var)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!export_var_path("PWD=", cwd, environ_var) || \
	!export_var_path("OLDPWD=", old_cwd, environ_var))
	{
		ft_free_str(&cwd);
		return (0);
	}
	ft_free_str(&cwd);
	ft_free_str(&old_cwd);
	return (1);
}

static int	get_directory(char **args, char ***environ_var, char **directory)
{
	int		i;

	errno = 138;
	i = 1;
	while (args[i] != NULL)
		i++;
	if (i == 1)
		*directory = ft_getenv("HOME", *environ_var);
	else
		*directory = args[1];
	return (i);
}

int	builtin_cd(char **args, char ***environ_var)
{
	char	*directory;
	char	*old_cwd;
	int		i;

	directory = NULL;
	i = get_directory(args, environ_var, &directory);
	if (directory == NULL)
		return (0);
	old_cwd = getcwd(NULL, 0);
	if (chdir(directory) == -1)
	{
		if (i == 1)
			ft_free_str(&directory);
		ft_free_str(&old_cwd);
		return (0);
	}
	if (i == 1)
		ft_free_str(&directory);
	if (!export_pwd_vars(old_cwd, environ_var))
		return (0);
	return (1);
}
