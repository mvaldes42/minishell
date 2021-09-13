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

static int	search_functions(t_data *data, t_token *token, t_searcher *srch)
{
	int			i;
	const char	*buildin[14] = \
	{"echo", "cd", "pwd", "export", "unset", "env", "exit", \
	"ECHO", "CD", "PWD", "EXPORT", "UNSET", "ENV", NULL};

	i = -1;
	while (buildin[++i])
	{
		if (ft_strncmp(token->ptr, buildin[i], ft_strlen(token->ptr)) == 0 \
		&& ft_strncmp(token->ptr, buildin[i], ft_strlen(buildin[i])) == 0)
		{
			token->type = BUILTIN;
			data->pars.cmd_nbr++;
			token->modif_word = ft_strdup(token->ptr);
			return (1);
		}
	}
	if (search_funct_ext(&data->pars, token, srch) == 1)
		return (1);
	errno = CMD_NOT_FOUND;
	return (0);
}

static int	rm_quotes_next(char *expanded_word, char *unquoted, int size)
{
	int		i;
	int		j;
	int		quotes_removed;

	i = 0;
	j = 0;
	quotes_removed = 0;
	while (i < size + 2 && j < size)
	{
		if (expanded_word[i] == S_QUOTE)
		{
			i += 1;
			while (i < size + 1 && j < size && expanded_word[i] != S_QUOTE)
				unquoted[j++] = expanded_word[i++];
			quotes_removed = 1;
			i += 1;
		}
		if (expanded_word[i] == D_QUOTE)
		{
			i += 1;
			while (i < size + 1 && j < size && expanded_word[i] != D_QUOTE)
				unquoted[j++] = expanded_word[i++];
			quotes_removed = 1;
			i += 1;
		}
		unquoted[j++] = expanded_word[i++];
	}
	unquoted[j] = 0;
	return (quotes_removed);
}

static int	remove_quotes(char **expanded_word)
{
	int		quotes_removed;
	char	*unquoted;
	int		size;

	if (*expanded_word == NULL)
		return (1);
	size = ft_strlen(*expanded_word) - 1;
	if (size <= 0)
		return (1);
	unquoted = malloc(sizeof(char *) * size);
	if (!unquoted)
		return (0);
	quotes_removed = rm_quotes_next(*expanded_word, unquoted, size);
	if (quotes_removed)
	{
		ft_free_str (expanded_word);
		(*expanded_word) = unquoted;
	}
	else
		ft_free_str(&unquoted);
	return (1);
}

void	search_path_str(t_searcher *srch)
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
		ft_free_str(&path_ptr);
		i++;
	}
	if (environ[i] == NULL)
		srch->env_path = NULL;
	else
	{
		srch->env_path = ft_split(path + 5, ':');
		ft_free_str(&path_ptr);
	}
}

int	expand_word(t_data *d, t_searcher *s)
{
	int			i;
	t_token		*tk;

	i = -1;
	while (++i < d->pars.tk_nbr)
	{
		tk = &d->pars.tks[i];
		tk->modif_word = NULL;
		if (ft_strncmp(".", tk->ptr, ft_strlen(tk->ptr)) == 0 \
		|| ft_strncmp("..", tk->ptr, ft_strlen(tk->ptr)) == 0)
			break ;
		if (tk->type == WORD)
		{
			if (!search_variables(d, tk, s, d->environ))
				return (0);
			if (i == 0 || (i > 0 && d->pars.tks[i - 1].type == PIPE))
				if (!search_functions(d, tk, s))
					return (0);
		}
		else if (tk->type == EXIT_STS)
			tk->modif_word = ft_strdup("exit_status(do do later)");
		else
			tk->modif_word = ft_strdup(tk->ptr);
		if (!remove_quotes(&tk->modif_word))
			return (0);
	}
	return (1);
}