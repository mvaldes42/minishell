/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 15:33:32 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/21 14:06:46 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static int	quotes_unquoted(char *exp, char **unquoted, int *i, int quote_t)
{
	if (exp[++(*i)] == quote_t)
		*(*unquoted) = ' ';
	while (*i <= (int)ft_strlen(exp) - 1 && **unquoted && exp[*i] != quote_t)
		*((*unquoted)++) = exp[(*i)++];
	return (2);
}

static int	rm_quotes_unquoted(char *exp, char *unquoted, int max, int q_rm)
{
	int		i;

	i = 0;
	while (i <= max && *unquoted)
	{
		if (i <= max && exp[i] == S_QUOTE)
			q_rm += quotes_unquoted(exp, &unquoted, &i, S_QUOTE);
		else if (i <= max && exp[i] == D_QUOTE)
			q_rm += quotes_unquoted(exp, &unquoted, &i, D_QUOTE);
		else if (i <= max)
			*(unquoted++) = exp[i];
		i++;
	}
	*unquoted = 0;
	return (q_rm);
}

static void	quotes_size(char *exp, int *i, int *nbr_removed, int quote_t)
{
	if (exp[++(*i)] == quote_t)
		*nbr_removed -= 1;
	while (*i < (int)ft_strlen(exp) && exp[(*i)++] != quote_t)
		;
	*nbr_removed += 2;
	*i += 1;
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
			quotes_size(exp, &i, &nbr_removed, S_QUOTE);
		else if (i < size && exp[i] == D_QUOTE)
			quotes_size(exp, &i, &nbr_removed, D_QUOTE);
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
	unquoted = (char *)malloc(sizeof(char) * (size + 1));
	if (!unquoted)
		return (0);
	ft_memset(unquoted, '0', sizeof(char) * (size + 1));
	q_rm = 0;
	unquoted_ptr = unquoted;
	q_rm = rm_quotes_unquoted(*exp, unquoted, (int)ft_strlen(*exp) - 1, q_rm);
	if (q_rm)
	{
		ft_free_str(exp);
		(*exp) = unquoted_ptr;
	}
	else
		ft_free_str(&unquoted_ptr);
	return (1);
}
