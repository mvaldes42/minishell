/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:35:29 by mvaldes           #+#    #+#             */
/*   Updated: 2020/01/09 13:17:56 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	if (dst != NULL && src != NULL && src != dst)
	{
		while (n--)
		{
			*(unsigned char *)dst++ = *(unsigned char *)src;
			if (*(unsigned char *)src++ == (unsigned char)c)
				return (dst);
		}
	}
	return (NULL);
}
