/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 12:05:53 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/24 14:12:01 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	word_count(const char *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c && s[i] != '\'')
		{
			while (s[i] && s[i] != c && s[i] != '\'')
				i++;
			count++;
		}
		if (s[i] && s[i] == '\'')
		{
			i += 1;
			while (s[i] && s[i] != '\'')
				i++;
			count++;
			i += 1;
		}
	}
	return (count);
}

static char	**no_occurence(char **dest, const char *s)
{
	dest[0] = ft_strdup(s);
	dest[1] = 0;
	return (dest);
}

static char	**ft_split2(char const *s, char c, char **dest)
{
	int		start;
	int		end;
	int		i;

	start = 0;
	end = 0;
	i = 0;
	while (i != word_count(s, c))
	{
		while (s[start] && s[start] == c)
			start++;
		if (!s[start])
			return (no_occurence(dest, s));
		end = start;
		while (s[end] != c && s[end])
			end++;
		dest[i] = ft_substr(s, start, (end - start));
		i++;
		start = end;
	}
	dest[i] = 0;
	return (dest);
}

	// while (s[i])
	// {
	// 	while (s[i] && s[i] == c)
	// 		i++;
	// 	if (s[i] && s[i] != c && s[i] != '\'')
	// 	{
	// 		while (s[i] && s[i] != c && s[i] != '\'')
	// 			i++;
	// 		count++;
	// 	}
	// 	if (s[i] && s[i] == '\'')
	// 	{
	// 		i += 1;
	// 		while (s[i] && s[i] != '\'')
	// 			i++;
	// 		count++;
	// 		i += 1;
	// 	}
	// }

char	**ft_split(char const *s, char c)
{
	char	**dest;

	if (!(s))
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!dest)
		return (NULL);
	return (ft_split2(s, c, dest));
}
