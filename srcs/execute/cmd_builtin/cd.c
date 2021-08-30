/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:06:50 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/30 15:16:46 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../../minishell.h"

int	builtin_cd(char **args, char **environ_var)
{
	char	*directory;
	int		i;

	(void)environ_var;
	i = 1;
	while (args[i] != NULL)
		i++;
	if (i == 1)
		directory = getenv("HOME");
	else
		directory = args[1];
	if (chdir(directory) == -1)
		return (0);
	return (1);
}
