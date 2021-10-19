/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:34:58 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/19 11:14:55 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	if (split)
	{
		while (split[++i])
			ft_free_str(&split[i]);
		free(split);
		split = NULL;
	}
}

int	is_name_valid(char *str)
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
