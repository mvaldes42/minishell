/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 10:48:45 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/22 19:40:45 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_on_set(const char *set, int c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	find_index(const char *s1, const char *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (is_on_set(set, s1[i]))
			i++;
		else
			return (i);
	}
	return (0);
}

static int	find_index_rev(const char *s1, const char *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (s1[i])
	{
		if (is_on_set(set, s1[i]))
			i--;
		else
			return (i);
	}
	return (0);
}

static size_t	ft_occurs(char const *set, char const *s1)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if (is_on_set(set, s1[i]))
			i++;
		else
			return (i);
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int			start;
	int			end;
	char		*result;

	if (!s1 || set == NULL || s1[0] == '\0')
		return (ft_strdup(""));
	if (ft_occurs(set, s1) == ft_strlen(s1))
	{
		result = (char *)malloc((ft_strlen(s1)) * sizeof(char));
		if (!result)
			return (NULL);
		ft_bzero(result, ft_strlen(s1));
		return (result);
	}
	start = find_index(s1, set);
	end = find_index_rev(s1, set);
	result = ft_substr(s1, start, (end + 1 - start));
	return (result);
}
