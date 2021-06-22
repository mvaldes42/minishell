/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:16:16 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/22 19:41:23 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	size_t	i;

	if (!s || !f)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	ft_bzero((void *)result, ft_strlen(s) + 1);
	ft_memcpy((void *)result, (const void *)s, ft_strlen(s) + 1);
	i = -1;
	while (*(result + ++i))
		*(result + i) = f(i, *(result + i));
	return (result);
}
