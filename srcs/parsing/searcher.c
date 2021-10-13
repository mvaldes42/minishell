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

static int	search_functions(t_data *data, t_token *token, char **env_path)
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
	if (search_funct_ext(&data->pars, token, env_path) == 1)
		return (1);
	token->type = FUNCTION;
	data->pars.cmd_nbr++;
	token->modif_word = NULL;
	token->tk_fct_path = NULL;
	errno = CMD_NOT_FOUND;
	return (0);
}

void	search_path_str(t_data *d, char ***env_path)
{
	int			i;
	char		*path_ptr;
	char		*path;

	i = 0;
	path = NULL;
	errno = ENOENT;
	while (d->environ[i] != NULL)
	{
		path_ptr = path;
		path = ft_strnstr(d->environ[i], "PATH=", 5);
		if (path != NULL)
			break ;
		ft_free_str(&path_ptr);
		i++;
	}
	if (d->environ[i] == NULL)
		*env_path = NULL;
	else
	{
		*env_path = ft_split(path + 5, ':');
		ft_free_str(&path_ptr);
	}
}

int	expand_word(t_data *d, char **env_path, int i)
{
	if (d->pars.tks[i].type == WORD)
	{
		if (!search_variables(d, i, d->environ))
			return (0);
		if (i == 0 || (i > 0 && d->pars.tks[i - 1].type == PIPE))
			if (!search_functions(d, &d->pars.tks[i], env_path))
				return (0);
	}
	else if (d->pars.tks[i].type == EXIT_STS)
		d->pars.tks[i].modif_word = ft_strdup("exit_status(do do later)");
	else
		d->pars.tks[i].modif_word = ft_strdup(d->pars.tks[i].ptr);
	return (1);
}
