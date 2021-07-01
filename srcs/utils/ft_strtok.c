/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 17:23:31 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/01 14:47:03 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static size_t	ft_strcspn(const char *s1, const char *s2)
{
	const char	*s;
	const char	*c;

	s = s1;
	while (*s1)
	{
		c = s2;
		while (*c)
		{
			if (*s1 == *c)
				break ;
			c++;
		}
		if (*c)
			break ;
		s1++;
	}
	return (s1 - s);
}

static size_t	ft_strspn(const char *s1, const char *s2)
{
	const char	*s;
	const char	*c;

	s = s1;
	while (*s1)
	{
		c = s2;
		while (*c)
		{
			if (*s1 == *c)
				break ;
			c++;
		}
		if (*c == '\0')
			break ;
		s1++;
	}
	return (s1 - s);
}

static char	*ft_strtok_r(char *s, const char *delim, char **save_ptr)
{
	char	*end;

	if (s == NULL)
		s = *save_ptr;
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	s += ft_strspn(s, delim);
	if (*s == '\0')
	{
		*save_ptr = s;
		return (NULL);
	}
	end = s + ft_strcspn(s, delim);
	if (*end == '\0')
	{
		*save_ptr = end;
		return (s);
	}
	*end = '\0';
	*save_ptr = end + 1;
	return (s);
}

char	*ft_strtok(char *s, const char *delim)
{
	static char	*olds;

	return (ft_strtok_r(s, delim, &olds));
}
