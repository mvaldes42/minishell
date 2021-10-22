/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:56 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 09:41:36 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	builtin_pwd(char **args, int argc, char ***environ_var)
{
	char	*pwd;

	(void)args;
	(void)argc;
	(void)environ_var;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		g_error = errno;
		return (0);
	}
	printf("%s\n", pwd);
	ft_free_str(&pwd);
	return (1);
}
