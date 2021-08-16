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

static int	search_variables(t_token *token, t_searcher *srch)
{
	char	*translated_str;
	char	*ptr;

	errno = VAR_NOT_FOUND;
	if (token->type == VARIABLE)
	{
		translated_str = ft_strdup(token->ptr);
		ptr = translated_str;
		translated_str++;
		token->trans_var = getenv(translated_str);
		ft_free(ptr);
		if (token->trans_var == NULL)
			return (0);
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
		ft_strlen(buildin[i])) == 0)
		{
			token->type = BUILTIN;
			data->pars.cmd_nbr++;
			return (1);
		}
		i++;
	}
	if (search_funct_ext(&data->pars, token, srch) == 1)
		return (1);
	return (0);
}

static int	searcher_bis(t_data *d, t_token *tk, t_searcher	*srch)
{
	if (tk->type == VARIABLE || tk->type == WEAK_WORD)
	{
		if (!search_variables(tk, srch))
			return (0);
		search_functions(d, tk, srch);
	}
	if (tk->type == EXIT_STS)
		tk->trans_weak = ft_strdup("exit_status(do do later)");
	return (1);
}

static void	search_path_str(t_searcher *srch)
{
	int			i;
	char		*path_ptr;
	char		*path;
	extern char	**environ;

	i = 0;
	path = NULL;
	errno = ENOENT;
	while (environ[i] != NULL)
	{
		path_ptr = path;
		path = ft_strnstr(environ[i], "PATH=", 5);
		if (path != NULL)
			break ;
		ft_free(path_ptr);
		i++;
	}
	if (environ[i] == NULL)
		srch->env_path = NULL;
	else
	{
		srch->env_path = ft_split(path + 5, ':');
		ft_free(path_ptr);
	}
}

int	searcher(t_data *d)
{
	int			i;
	t_token		*tk;
	t_searcher	s;

	ft_memset(&s, 0, sizeof(t_searcher));
	search_path_str(&s);
	i = -1;
	while (++i < d->pars.tk_nbr)
	{
		tk = &d->pars.tks[i];
		if (ft_strncmp(".", tk->ptr, ft_strlen(tk->ptr)) == 0 \
		|| ft_strncmp("..", tk->ptr, ft_strlen(tk->ptr)) == 0)
			break ;
		if (!searcher_bis(d, tk, &s))
			return (0);
		else if (tk->type == WORD && \
		(i == 0 || d->pars.tks[i - 1].type == PIPE))
			if (!search_functions(d, tk, &s))
				break ;
	}
	if (!free_searcher(d, &s))
		return (0);
	return (1);
}
