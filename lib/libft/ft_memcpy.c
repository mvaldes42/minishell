/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 14:13:32 by mvaldes           #+#    #+#             */
/*   Updated: 2020/01/09 14:51:55 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*tpsrc;
	unsigned char	*tpdst;

	tpdst = (unsigned char *)dst;
	tpsrc = (unsigned char *)src;
	if (dst != NULL && src != NULL && src != dst && n != 0)
	{
		while (n--)
		{
			*tpdst = *tpsrc;
			tpdst++;
			tpsrc++;
		}
	}
	return (dst);
}
