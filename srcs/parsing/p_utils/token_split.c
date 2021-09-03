/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 15:23:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/03 15:43:38 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

char	**token_split(char const *str, int token_nbr)
{
	t_split		s_data;

	if (!(str))
		return (NULL);
	ft_memset(&s_data, 0, sizeof(t_split));
	s_data.w_count = token_nbr;
	s_data.dest = (char **)malloc(sizeof(char *) * (s_data.w_count + 1));
	if (!s_data.dest)
		return (NULL);
	special_split_2(&s_data, str);
	s_data.dest[s_data.w_count] = NULL;
	return (s_data.dest);
}
