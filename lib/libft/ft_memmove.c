/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:53:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/22 19:35:48 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*dst_cp;
	char	*src_cp;

	if (dst != NULL && src != NULL && dst != src)
	{
		dst_cp = (char *)dst;
		src_cp = (char *)src;
		if (src_cp <= dst_cp)
		{
			while (len--)
				((unsigned char *)dst_cp)[len] = ((unsigned char *)src_cp)[len];
		}
		else
		{
			i = 0;
			while (i < len)
			{
				((unsigned char *)dst_cp)[i] = ((unsigned char *)src_cp)[i];
				i++;
			}
		}
		return (dst_cp);
	}
	return (NULL);
}
