/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:14:55 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/22 19:35:12 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	i = 0;
	if (s1 != NULL && s2 != NULL && s1 != s2 && n != 0)
	{
		str1 = (const unsigned char *)s1;
		str2 = (const unsigned char *)s2;
		while (i < n)
		{
			if (str1[i] != str2[i])
				return ((int)(str1[i] - str2[i]));
			i++;
		}
	}
	return (0);
}
