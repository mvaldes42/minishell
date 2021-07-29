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

static int	weak_word_search(t_token_id *token, t_searcher *srch)
{
	char	*o_s;

	o_s = ft_strdup(token->token_ptr);
	srch->nbr_var = count_variables(o_s);
	original_var_length(o_s, srch);
	if (!translated_var_length(srch))
		return (0);
	srch->t_token_len = ft_strlen(o_s) - \
	(srch->tot_o_len + 1) + srch->tot_t_len - 2;
	token->translated_tk = replace_substr(srch, o_s, srch->t_token_len);
	free(o_s);
	free_srch_struct(srch);
	return (1);
}

static int	search_variables(t_token_id *token, t_searcher *srch)
{
	char	*translated_str;

	if (token->token_type == VARIABLE)
	{
		translated_str = ft_strdup(token->token_ptr);
		translated_str++;
		token->translated_var = getenv(translated_str);
		if (token->translated_var == NULL)
		{
			printf("\n");
			return (0);
		}
	}
	else if (token->token_type == WEAK_WORD)
		if (!weak_word_search(token, srch))
			return (0);
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
	path_ptr = path;
	while (environ[i] != NULL)
	{
		if (ft_strnstr(environ[i], "PATH=", 5) != NULL)
			path = ft_strnstr(environ[i], "PATH=", 5);
		i++;
	}
	srch->path_str = ft_split(path + 5, ':');
	free(path_ptr);
}

static int	search_funct_ext(t_data *data, t_token_id *token, t_searcher *srch)
{
	struct stat	statbuf;
	char		*dest_dir;
	int			size;
	int			i;

	i = 0;
	while (srch->path_str[i] != NULL)
	{
		size = sizeof(char) * (ft_strlen(srch->path_str[i]) + ft_strlen("/") + \
		ft_strlen(srch->path_str[i]) + 1);
		dest_dir = (char *)malloc(size);
		if (dest_dir == NULL)
			return (0);
		ft_strlcat(dest_dir, srch->path_str[i], size);
		ft_strlcat(dest_dir, "/", size);
		ft_strlcat(dest_dir, token->token_ptr, size);
		if (stat(dest_dir, &statbuf) == 0)
		{
			printf("%s\n", dest_dir);
			data->s_tokens.commands_nbr++;
			free(dest_dir);
			return (1);
		}
		free(dest_dir);
		i++;
	}
	return (1);
}
// au return (1)

static int	search_functions(t_data *data, t_token_id *token, t_searcher *srch)
{
	int			i;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(token->token_ptr, g_build_in[i], \
		ft_strlen(token->token_ptr)) == 0)
		{
			data->s_tokens.commands_nbr++;
			return (1);
		}
		i++;
	}
	if (search_funct_ext(data, token, srch) == 1)
		return (1);
	return (0);
}

int	searcher(t_data *data)
{
	int			i;
	t_parsing	*parsing;
	t_token_id	*token;
	t_searcher	srch;

	parsing = &data->s_tokens;
	ft_memset(&srch, 0, sizeof(t_searcher));
	search_path_str(&srch);
	i = 0;
	while (i < parsing->tk_nbr)
	{
		token = &parsing->tk_lst[i];
		if (token->token_type == VARIABLE || token->token_type == WEAK_WORD)
			if (!search_variables(token, &srch))
				return (0);
		if (token->token_type == EXIT_STS)
			token->translated_tk = ft_strdup("exit_status(do do later)");
		if (token->token_type == WORD && \
		(i == 0 || parsing->tk_lst[i - 1].token_type == PIPE))
			search_functions(data, token, &srch);
		i++;
	}
	return (1);
}
