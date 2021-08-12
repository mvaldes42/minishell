/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:43:33 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/12 18:41:25 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

void	test(void)
{
	extern char	**environ;
	int			i;

	i = 0;
	while (environ[i])
	{
		printf("%d: %s\n", i, environ[i]);
		i++;
	}
}

// int	builtin_export(char **args)
// {
// 	extern char	**environ;
// 	int			size;
// 	char		*p;
// 	int			i;

// 	(void)args;
// 	i = 0;
// 	// size = 0;
// 	// p = NULL;
// 	// while (environ[i])
// 	// {
// 	// 	// printf("%d: %s\n", i, environ[i]);
// 	// 	size++;
// 	// 	p++;
// 	// 	i++;
// 	// }
// 	for (p = *environ, size = 0; *p; ++p, ++size);
// 	printf("size: %d\n", size);
// 	printf("pointer %p & size: %zu\n\n\n", environ, ft_strlen(*environ));
// 	p = malloc((size_t)(sizeof(char *) * (size + 2)));
// 	if (!p)
// 		return (-1);
// 	memmove(*environ, p, size * sizeof(char *));
// 	*environ = p;
// 	environ[size + 1] = NULL;
// 	// i = -1;
// 	// while (environ[++i])
// 	// 	printf("%d: %s\n", i, environ[i]);
// 	printf("pointer %p & size: %zu\n", environ, ft_strlen(*environ));
// 	test();
// 	return (1);
// }

int	builtin_export(char **args)
{
	extern char	**environ;
	int			size;
	char		*p;
	int			i;

	(void)args;
	i = 0;
	size = 0;
	p = NULL;
	while (environ[size])
		size++;
	// size = 32;
	printf("size: %d\n", size);
	printf("pointer %p & size: %zu\n\n\n", environ, ft_strlen(*environ));
	p = malloc(sizeof(char *) * (size + 2));
	memmove(p, *environ, size * sizeof(char *));
	if (!p)
		return (-1);
	// *environ = p;
	free(p);
	environ[size] = "lollls";
	environ[size + 1] = NULL;
	printf("pointer %p & size: %zu\n", environ, ft_strlen(*environ));
	test();
	return (1);
}
