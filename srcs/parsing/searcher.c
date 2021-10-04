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
	token->type = FUNCTION;
	data->pars.cmd_nbr++;
	token->modif_word = NULL;
	token->tk_fct_path = NULL;
	return (1);
}

static int	rm_quotes_next(char *exp_word, char *unquoted, int size, int q_rm)
{
	int		i;

	i = 0;
	printf("exp_word : %s\n", exp_word);
	while (i < (int)ft_strlen(exp_word) && *unquoted)
	{
		if (exp_word[i] == S_QUOTE)
		{
			i += 1;
			while (i < size + 1 && *unquoted && exp_word[i] != S_QUOTE)
			{
				*unquoted = exp_word[i];
				printf("(single quote) exp_word[i] : %c\n", exp_word[i]);
				i++;
				unquoted++;
			}
			q_rm += 2;
			i += 1;
		}
		else if (exp_word[i] == D_QUOTE)
		{
			i += 1;
			while (i < size + 1 && *unquoted && exp_word[i] != D_QUOTE)
			{
				*unquoted = exp_word[i];
				printf("(double quote) exp_word[%d] : %c\n", i, exp_word[i]);
				i++;
				unquoted++;
			}
			q_rm += 2;
			i += 1;
		}
		if (i < (int)ft_strlen(exp_word) && exp_word[i] != D_QUOTE && exp_word[i] != S_QUOTE)
		{
			*unquoted = exp_word[i];
			printf("(double quote) exp_word[%d] : %c\n", i, exp_word[i]);
			unquoted++;
		}
		i++;
	}
	*unquoted = 0;
	return (q_rm);
}

static int	size_of_unquoted(char *expanded_word)
{
	int	size;
	int	nbr_removed;
	int	i;

	size = ft_strlen(expanded_word);
	nbr_removed = 0;
	i = -1;
	while (i < size && expanded_word[++i])
	{
		if (i < size && expanded_word[i] == S_QUOTE)
		{
			while (i < size && expanded_word[++i] != S_QUOTE)
				;
			nbr_removed += 2;
			i += 1;
		}
		if (i < size && expanded_word[i] == D_QUOTE)
		{
			while (i < size && expanded_word[++i] != D_QUOTE)
				;
			nbr_removed += 2;
			i += 1;
		}
	}
	return (size - nbr_removed);
}

int	remove_quotes(char **expanded_word)
{
	int		q_rm;
	char	*unquoted;
	int		size;
	char	*unquoted_ptr;

	if (*expanded_word == NULL)
		return (1);
	size = size_of_unquoted(*expanded_word);
	printf("size_of_unquoted: %d\n", size);
	if (size <= 0 || size == (int)ft_strlen(*expanded_word))
		return (1);
	unquoted = malloc(sizeof(char *) * (size + 1));
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
		if (!search_variables(d, i, s, d->environ))
			return (0);
		if (i == 0 || (i > 0 && d->pars.tks[i - 1].type == PIPE))
			if (!search_functions(d, &d->pars.tks[i], s))
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