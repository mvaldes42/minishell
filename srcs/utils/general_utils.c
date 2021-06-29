/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:25 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/29 19:44:48 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_fail(t_data *data)
{
	(void)data;
	ft_putstr_fd("Error\n", STDERR);
	exit(EXIT_FAILURE);
}

void	print_prompt(void)
{
	char	cwd[256];

	ft_putstr_fd("-> ", STDOUT);
	ft_putstr_fd(getcwd(cwd, sizeof(cwd)), STDOUT);
	ft_putstr_fd(" >$ ", STDOUT);
}