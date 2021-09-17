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
	const char	*buildin[] = \
	{"echo", "cd", "pwd", "export", "unset", "env", "exit", \
	"ECHO", "PWD", "ENV", NULL};

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

static int	rm_quotes_next(char *exp_word, char *unquoted, int size, int q_rm)
{
	int		i;

	i = 0;
	while (i < size + 2 && *unquoted)
	{
		if (exp_word[i] == S_QUOTE)
		{
			i += 1;
			while (i < size + 1 && *unquoted && exp_word[i] != S_QUOTE)
				*(unquoted++) = exp_word[i++];
			q_rm = 1;
			i += 1;
		}
		if (exp_word[i] == D_QUOTE)
		{
			i += 1;
			while (i < size + 1 && *unquoted && exp_word[i] != D_QUOTE)
				*(unquoted++) = exp_word[i++];
			q_rm = 1;
			i += 1;
		}
		*(unquoted++) = exp_word[i++];
	}
	*unquoted = 0;
	return (q_rm);
}

int	remove_quotes(char **expanded_word)
{
	int		q_rm;
	char	*unquoted;
	int		size;
	char	*unquoted_ptr;

	if (*expanded_word == NULL)
		return (1);
	size = ft_strlen(*expanded_word) - 1;
	if (size <= 0)
		return (1);
	unquoted = malloc(sizeof(char *) * size);
	if (!unquoted)
		return (0);
	q_rm = 0;
	unquoted_ptr = unquoted;
	q_rm = rm_quotes_next(*expanded_word, unquoted, size, q_rm);
	if (q_rm)
	{
		ft_free_str(expanded_word);
		(*expanded_word) = unquoted_ptr;
	}
	else
		ft_free_str(&unquoted_ptr);
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

int	expand_word(t_data *d, t_searcher *s, int i)
{
	if (d->pars.tks[i].type == WORD)
	{
		if (!search_variables(d, &d->pars.tks[i], s, d->environ))
			return (0);
		if (i == 0 || (i > 0 && d->pars.tks[i - 1].type == PIPE))
			if (!search_functions(d, &d->pars.tks[i], s))
				return (0);
	}
	else if (d->pars.tks[i].redir)
	{
		errno = UNEXPECTED_TK;
		if (i + 1 > d->pars.tk_nbr || d->pars.tks[i + 1].type != WORD)
			return (0);
	}
	else if (d->pars.tks[i].type == EXIT_STS)
		d->pars.tks[i].modif_word = ft_strdup("exit_status(do do later)");
	else
		d->pars.tks[i].modif_word = ft_strdup(d->pars.tks[i].ptr);
	return (1);
}

// printf("(expand word) > tk[%d]: %s, d->pars.tk_nbr: %d\n",
// i, tk->modif_word, d->pars.tk_nbr);