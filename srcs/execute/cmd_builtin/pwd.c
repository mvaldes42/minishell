/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:56 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/17 15:09:10 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	builtin_pwd(char **args, char ***environ_var)
{
	char	*pwd;

	(void)args;
	(void)environ_var;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (1);
	printf("%s\n", pwd);
	ft_free_str(&pwd);
	return (0);
}
