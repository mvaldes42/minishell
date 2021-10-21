/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:56 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/14 11:38:57 by fcavillo         ###   ########.fr       */
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
		return (0);
	printf("%s\n", pwd);
	ft_free_str(&pwd);
	return (1);
}
