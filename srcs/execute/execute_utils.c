/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:34:58 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 14:27:27 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"

void	free_split(char ***split)
{
	int	i;

	i = -1;
	if (*split != NULL)
	{
		while ((*split)[++i])
		{
			ft_free_str(&(*split)[i]);
		}
		free(*split);
		*split = NULL;
	}
}

int	is_name_valid_unset(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!((str[i] >= 'A' && str[i] <= 'Z') || \
		(str[i] >= 'a' && str[i] <= 'z') || str[i] == '_'))
		{
			g_error = INV_NAME;
			return (0);
		}
	}
	return (1);
}

int	is_name_valid(char *str)
{
	int		i;
	char	**split;

	g_error = INV_NAME;
	split = ft_split(str, '=');
	if (!split || split[0] == NULL)
		return (0);
	if (split[1] == NULL)
		return (-1);
	g_error = 0;
	i = -1;
	while (split[0][++i])
	{
		if (!((split[0][i] >= 'A' && split[0][i] <= 'Z') || \
		(split[0][i] >= 'a' && split[0][i] <= 'z') || split[0][i] == '_'))
		{
			free_split(&split);
			return (0);
		}
	}
	free_split(&split);
	return (1);
}
