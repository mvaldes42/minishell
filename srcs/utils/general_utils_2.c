/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 12:07:39 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/21 10:19:44 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

void	ft_free_int(int **int_ptr)
{
	if (*int_ptr != NULL)
	{
		free(*int_ptr);
		*int_ptr = NULL;
	}
}

void	ft_free_str(char **str_ptr)
{
	if (*str_ptr)
	{
		free(*str_ptr);
		*str_ptr = NULL;
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

int	error_handling(t_data *data)
{
	static char	*errors[] = {"missing quote", "", "command not found", \
	"syntax error near unexpected token", "", "not a valid identifier", \
	"HOME not set", "builtin address points to the zero page", ""};
	int			i;

	if (errno > 131)
	{
		i = errno - 131 - 1;
		if (errno == VAR_NOT_FOUND)
			printf("%s\n", errors[i]);
		else if (errno == EMPTY_LINE || errno == UNSET_NOT_FOUND)
			;
		else
			printf("minishell: %s\n", errors[i]);
	}
	else
		printf("minishell: %s\n", strerror(errno));
	ft_free_str(&data->environ[0]);
	// printf("g_minishell.exit_status : %d\n", g_minishell.exit_status);
	// if (g_minishell.exit_status != 0)
	// 	data->environ[0] = ft_strdup("?=ft_itoa(g_minishell.exit_status)");
	// else
	printf("%d\n", errno);
		data->environ[0] = ft_strdup("?=1");
	return (1);
}

char	*ft_getenv(const char *name, char **env_var)
{
	int		i;
	char	**split_env;
	char	*result;

	i = -1;
	while (env_var[++i])
	{
		split_env = ft_split(env_var[i], '=');
		if (ft_strncmp(name, split_env[0], ft_strlen(split_env[0])) == 0 && \
		ft_strncmp(name, split_env[0], ft_strlen(name)) == 0)
		{
			result = ft_strdup(split_env[1]);
			free_split(&split_env);
			return (result);
		}
		free_split(&split_env);
	}
	return (NULL);
}
