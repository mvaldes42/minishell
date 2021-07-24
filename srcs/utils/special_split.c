/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 15:23:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/24 15:23:32 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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

static int	regu_word(int start, int end, int i, char const *s, char c, char **dest)
{
	while (s[end] && s[end] != c && s[end] != '\'')
		end++;
	dest[i] = ft_substr(s, start, (end - start));
	return (end);
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
		if (s[end] && s[end] != c && s[end] != '\'')
		{
			regu_word(start, end, i, s, c, dest);
			i++;
		}
		if (s[end] && s[end] == '\'')
		{
			end += 1;
			while (s[end] && s[end] != '\'')
				end++;
			end += 1;
			dest[i] = ft_substr(s, start, (end - start));
			i++;
		}
		start = end;
	}
	dest[i] = NULL;
	return (dest);
}

char	**special_split(char const *s, char c)
{
	char	**dest;

	if (!(s))
		return (NULL);
	dest = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (!dest)
		return (NULL);
	return (ft_split2(s, c, dest));
}