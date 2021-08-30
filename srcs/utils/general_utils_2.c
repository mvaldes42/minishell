/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 12:07:39 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/27 16:48:11 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	ft_free(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	create_prompt(t_data *data, int fail)
{
	char	cwd[256];
	int		size;
	char	*cross;
	char	*arrow;

	cross = P_ESC_SEQ " " RL_S "\033[38;5;11m" RL_E "\u2613" P_ESC_SEQ " ";
	if (fail)
		arrow = RL_S "\033[91m" RL_E "\u27A1" P_ESC_SEQ " " \
		RL_S "\033[48;5;57m" RL_E;
	else
		arrow = RL_S "\033[92m" RL_E "\u27A1" P_ESC_SEQ " " \
		RL_S "\033[48;5;57m" RL_E;
	getcwd(cwd, sizeof(cwd));
	size = ft_strlen(cwd) + ft_strlen(arrow) + ft_strlen(cross) + 1;
	data->prompt = (char *)malloc(sizeof(char) * size);
	ft_memset(data->prompt, 0, sizeof(data->prompt));
	ft_strlcat(data->prompt, arrow, size);
	ft_strlcat(data->prompt, cwd, size);
	ft_strlcat(data->prompt, cross, size);
}

int	error_handling(void)
{
	static char	*errors[] = {"missing quote", "", "command not found", \
	"syntax error near unexpected token", "", "not a valid identifier"};
	int			i;

	if (errno > 131)
	{
		i = errno - 131 - 1;
		if (errno == 133)
			printf("%s\n", errors[i]);
		else if (errno == 136)
			;
		else
			printf("minishell: %s\n", errors[i]);
	}
	else
		printf("minishell: %s\n", strerror(errno));
	return (1);
}
// rl_replace_line();
