/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:28:26 by mvaldes           #+#    #+#             */
/*   Updated: 2020/01/09 15:04:31 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	if (src != NULL && dst != NULL)
	{
		len = 0;
		while (dst[len] && len < dstsize)
			len++;
		i = len;
		while (src[len - i] && len + 1 < dstsize)
		{
			dst[len] = src[len - i];
			len++;
		}
		if (i < dstsize)
			dst[len] = '\0';
		return (i + ft_strlen(src));
	}
	return (0);
}
