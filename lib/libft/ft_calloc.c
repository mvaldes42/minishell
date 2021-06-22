/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 13:38:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/22 19:32:15 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if (count != 0 && size != 0)
	{
		result = malloc(size * count);
		if (!result)
			return (NULL);
		ft_bzero(result, size * count);
		return (result);
	}
	return (malloc(1));
}
