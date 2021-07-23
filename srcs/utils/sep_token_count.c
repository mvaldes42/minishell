/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sep_token_count.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:26:26 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/23 21:28:55 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	quotes_case(int count, char **s)
{
	if (**s == '\'')
	{
		count += 1;
		*s += 1 ;
		while (**s != '\'')
			*s += 1;
		*s += 1;
	}
	else if (**s == '\"')
	{
		count += 1;
		*s += 1 ;
		while (**s != '\"')
			*s += 1;
		*s += 1;
	}
	return (count);
}

static int	miscellaneous_case(int count, char **s, char *sep)
{
	if (**s == '$')
	{
		count += 1;
		*s += 1;
		while (**s != '\0' && ft_strrchr(sep, **s) == NULL)
			*s += 1;
	}
	else if (**s == '|')
	{
		count += 1;
		*s += 1;
	}
	return (count);
}

static int	redirect_case(t_data *data, int count, char **s)
{
	if (**s == '>')
	{
		*s += 1;
		if (**s == '<')
			exit_fail(data);
		count += 1;
		if (**s == '>')
			*s += 1;
	}
	else if (**s == '<')
	{
		*s += 1;
		if (**s == '>')
			exit_fail(data);
		count += 1;
		if (**s == '<')
			*s += 1;
	}
	return (count);
}

static int	word_case(int count, char **s, char *sep)
{
	if (**s == ' ')
	{
		while (**s == ' ')
			*s += 1;
	}
	else
	{
		count += 1;
		while (**s != '\0' && ft_strrchr(sep, **s) == NULL)
			*s += 1;
	}
	return (count);
}

int	sep_token_count(t_data *data, char *str, char *sep)
{
	int		count;
	char	*s;

	count = 0;
	s = str;
	while (*s != '\0')
	{
		if (*s == '\'' || *s == '\"')
			count = quotes_case(count, &s);
		else if (*s == '$' || *s == '|')
			count = miscellaneous_case(count, &s, sep);
		else if (*s == '>' || *s == '<')
			count = redirect_case(data, count, &s);
		else
			count = word_case(count, &s, sep);
	}
	return (count);
}
