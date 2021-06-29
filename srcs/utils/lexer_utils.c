/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:37 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/29 19:45:02 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	delim_token_count(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\'' || str[i] == '\"')
			i++;
		if (str[i])
			count++;
		while (!(str[i] == ' ' || str[i] == '\'' || str[i] == '\"') && str[i])
			i++;
		i++;
	}
	return (count);
}

int	char_occu(char *str, char c)
{
	int		nbr;
	char	*s;

	s = str;
	nbr = 0;
	while (*s)
	{
		if (*s == c)
			nbr++;
		s++;
	}
	if (nbr > 0)
		return (nbr);
	return (0);
}