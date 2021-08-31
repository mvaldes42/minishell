/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 11:34:58 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/31 11:21:04 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"

void	free_split(char **split)
{
	int	i;

	i = -1;
	while (split[++i])
		ft_free_str(&split[i]);
	free(split);
}
