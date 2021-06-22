/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:12:21 by mvaldes           #+#    #+#             */
/*   Updated: 2020/01/09 13:11:38 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*start;

	if (b != NULL)
	{
		start = (unsigned char *)b;
		while (len)
		{
			*start = (unsigned char)c;
			start++;
			len--;
		}
	}
	return (b);
}
