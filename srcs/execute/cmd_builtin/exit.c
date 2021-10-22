/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:19 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 09:39:39 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	builtin_exit(char **args, int argc, char ***environ_var)
{
	(void)args;
	(void)argc;
	(void)environ_var;
	ft_putstr_fd("exit\n", 1);
	return (1);
}
