/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:22:12 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/22 19:40:04 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	n;

	if (haystack != NULL && needle != NULL && *needle)
	{
		n = ft_strlen(needle);
		while (*haystack && len-- >= n)
		{
			if (ft_strncmp(haystack, needle, n) == 0)
				return ((char *)haystack);
			haystack++;
		}
		return (NULL);
	}
	return ((char *)haystack);
}
