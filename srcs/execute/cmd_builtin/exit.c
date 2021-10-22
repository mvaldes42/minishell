/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:42:19 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 14:16:13 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	builtin_exit(char **args, int argc, char ***environ_var)
{
	(void)args;
	(void)argc;
	(void)environ_var;
	ft_putstr_fd("exit", 1);
	return (1);
}
