/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:33:32 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 14:30:03 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static int	rm_quotes_next(char *exp, char *unquoted, int max, int q_rm)
{
	int		i;

	i = 0;
	while (i < max && *unquoted)
	{
		if (exp[i] == S_QUOTE)
		{
			while (i < max && *unquoted && exp[++i] != S_QUOTE)
				*(unquoted++) = exp[i];
			q_rm += 2;
			i += 1;
		}
		if (exp[i] == D_QUOTE)
		{
			while (i < max && *unquoted && exp[++i] != D_QUOTE)
				*(unquoted++) = exp[i];
			q_rm += 2;
			i += 1;
		}
		if (exp[i] != D_QUOTE && exp[i] != S_QUOTE)
			*(unquoted++) = exp[i];
		i++;
	}
	*unquoted = 0;
	return (q_rm);
}

static int	size_of_unquoted(char *exp)
{
	int	size;
	int	nbr_removed;
	int	i;

	size = ft_strlen(exp);
	nbr_removed = 0;
	i = -1;
	while (i < size && exp[++i])
	{
		if (i < size && exp[i] == S_QUOTE)
		{
			while (i < size && exp[++i] != S_QUOTE)
				;
			nbr_removed += 2;
			i += 1;
		}
		if (i < size && exp[i] == D_QUOTE)
		{
			while (i < size && exp[++i] != D_QUOTE)
				;
			nbr_removed += 2;
			i += 1;
		}
	}
	return (size - nbr_removed);
}

int	remove_quotes(char **exp)
{
	int		q_rm;
	char	*unquoted;
	int		size;
	char	*unquoted_ptr;

	if (*exp == NULL)
		return (1);
	size = size_of_unquoted(*exp);
	if (size <= 0 || size == (int)ft_strlen(*exp))
		return (1);
	unquoted = malloc(sizeof(char *) * (size + 1));
	if (!unquoted)
		return (0);
	q_rm = 0;
	unquoted_ptr = unquoted;
	q_rm = rm_quotes_next(*exp, unquoted, (int)ft_strlen(*exp) - 1, q_rm);
	if (q_rm)
	{
		ft_free_str(exp);
		(*exp) = unquoted_ptr;
	}
	else
		ft_free_str(&unquoted_ptr);
	return (1);
}
