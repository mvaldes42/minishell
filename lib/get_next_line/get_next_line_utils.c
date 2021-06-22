/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:05:45 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/22 18:51:53 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr_gnl(const char *s, int start, int len)
{
	char	*str;
	int		i;

	if (!s)
		return (NULL);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}

char	*ft_strdup_gnl(const char *s1)
{
	char	*dest;
	int		i;

	if (!s1)
		return (NULL);
	dest = (char *)malloc((ft_strlen_gnl(s1) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	dest[i] = '\0';
	return (dest);
}

char	*ft_joinstr_gnl(char *s1, char *s2)
{
	int		len;
	int		i;
	char	*dest;

	if (!s1)
		return (ft_strdup_gnl(s2));
	if (!s2)
		return (NULL);
	len = ft_strlen_gnl(s1);
	dest = (char *)malloc((len + ft_strlen_gnl(s2) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	free(s1);
	s1 = NULL;
	i = -1;
	while (s2[++i])
		dest[len + i] = s2[i];
	dest[len + i] = '\0';
	return (dest);
}

void	*ft_memmove_gnl(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (src < dst)
	{
		i = len;
		while (i > 0)
		{
			i--;
			((char *)dst)[i] = ((char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < len)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dst);
}
