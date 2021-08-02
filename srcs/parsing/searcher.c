/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:35:55 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/26 14:30:57 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"

static void	search_path_str(t_searcher *srch)
{
	int			i;
	char		*path_ptr;
	char		*path;
	extern char	**environ;

	i = 0;
	path = NULL;
	while (environ[i] != NULL)
	{
		path_ptr = path;
		path = ft_strnstr(environ[i], "PATH=", 5);
		if (path != NULL)
			break ;
		free(path_ptr);
		i++;
	}
	srch->env_path = ft_split(path + 5, ':');
	free(path_ptr);
}

static int	search_variables(t_token *token, t_searcher *srch)
{
	char	*translated_str;
	char	*ptr;

	if (token->type == VARIABLE)
	{
		translated_str = ft_strdup(token->ptr);
		ptr = translated_str;
		translated_str++;
		token->trans_var = getenv(translated_str);
		free(ptr);
		if (token->trans_var == NULL)
		{
			printf("\n");
			return (0);
		}
	}
	else if (token->type == WEAK_WORD)
		if (!weak_word_search(token, srch))
			return (0);
	return (1);
}

static int	search_functions(t_data *data, t_token *token, t_searcher *srch)
{
	int			i;
	const char	*buildin[7] = \
	{"echo", "cd", "pwd", "export", "unset", "env", "exit"};

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(token->ptr, buildin[i], \
		ft_strlen(token->ptr)) == 0)
		{
			token->type = BUILTIN;
			data->prng.cmd_nbr++;
			return (1);
		}
		i++;
	}
	if (search_funct_ext(&data->prng, token, srch) == 1)
		return (1);
	return (0);
}

int	searcher(t_data *data)
{
	int			i;
	t_parsing	*parsing;
	t_token		*token;
	t_searcher	srch;

	parsing = &data->prng;
	ft_memset(&srch, 0, sizeof(t_searcher));
	search_path_str(&srch);
	i = 0;
	while (i < parsing->tk_nbr)
	{
		token = &parsing->tks[i];
		if (token->type == VARIABLE || token->type == WEAK_WORD)
			if (!search_variables(token, &srch))
				return (0);
		if (token->type == EXIT_STS)
			token->trans_weak = ft_strdup("exit_status(do do later)");
		else if (token->type == WORD && \
		(i == 0 || parsing->tks[i - 1].type == PIPE))
			if (!search_functions(data, token, &srch))
				return (0);
		i++;
	}
	i = 0;
	while (srch.env_path[i])
		free(srch.env_path[i++]);
	free(srch.env_path);
	if (parsing->cmd_nbr == 0)
	{
		printf("no recognized functions\n");
		return (0);
	}
	return (1);
}
