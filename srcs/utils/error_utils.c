/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 10:44:36 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 17:19:22 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

static void	attribute_error_return(char **err_str, int error_code)
{
	int		size;
	char	*error_code_str;
	char	*start;

	if (*err_str != NULL)
		ft_free_str(err_str);
	if (error_code == 0)
		*err_str = ft_strdup("?=0");
	else
	{
		start = "?=";
		error_code_str = ft_itoa(error_code);
		size = ft_strlen(start) + ft_strlen(error_code_str) + 1;
		*err_str = malloc(sizeof(char) * (size));
		ft_memset(*err_str, 0, size);
		ft_strlcat(*err_str, start, size);
		ft_strlcat(*err_str, error_code_str, size);
		ft_free_str(&error_code_str);
	}
}

static void	error_handle_exc(t_data *data)
{
	if (g_error == CMD_NOT_FOUND)
	{
		printf("minishell: command not found\n");
		attribute_error_return(&data->environ[0], 127);
	}
	if (g_error >= UNSET_NOT_FOUND)
	{
		if (g_error == INV_NAME)
			printf("minishell: not a valid identifier\n");
		else if (g_error == H_NOT_SET)
			printf("minishell: HOME not set\n");
		if (g_error == BUILTIN_ERR)
		{
			printf("minishell: misuse of shell builtins\n");
			attribute_error_return(&data->environ[0], 2);
		}
		else if (g_error == NO_SUCH_FILE)
		{
			printf("minishell: no such file or directory\n");
			attribute_error_return(&data->environ[0], 127);
		}
		else if (g_error != UNSET_NOT_FOUND)
			attribute_error_return(&data->environ[0], 1);
	}
}

int	error_handling(t_data *data)
{
	static char	*errors[] = {"missing quote", "", \
	"syntax error near unexpected token", ""};

	if (errno && !g_error)
	{
		if (errno < 300)
			printf("minishell: %s\n", strerror(errno));
		else if (errno >= MISSING_QUOTE && errno <= UNEXPECTED_TK)
			printf("minishell : %s\n", errors[errno - 300]);
		if (errno != EMPTY_LINE)
			attribute_error_return(&data->environ[0], 1);
	}
	else if (g_error)
	{
		if (g_error == UNSET_NOT_FOUND)
			attribute_error_return(&data->environ[0], 0);
		else if (g_error == CMD_NOT_FOUND || g_error >= UNSET_NOT_FOUND)
			error_handle_exc(data);
		else
			attribute_error_return(&data->environ[0], g_error);
	}
	return (1);
}
