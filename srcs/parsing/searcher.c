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

static void	search_functions(t_data *data, t_token_id *token)
{
	int			i;
	// struct stat	statbuf;
	// char		*dest_dir;

	i = 0;
	while (i < 7)
	{
		if (ft_strncmp(token->token_ptr, g_build_in[i], \
		ft_strlen(token->token_ptr)) == 0)
		{
			data->s_tokens.commands_nbr++;
		}
		i++;
	}
	// i = 0;
	// while (data->path_str[i] != NULL)
	// {
	// 	dest_dir = malloc(sizeof(char) * (ft_strlen(data->path_str[i]) + \
	// 	ft_strlen(data->s_tokens.tk_lst[i].token_ptr) + 2));
	// 	// strcat(dest_dir, data->path_str[i]);
	// 	// strcat(dest_dir, "/");
	// 	// strcat(dest_dir, data->s_tokens.tk_lst[i].token_ptr);
	// 	// if (stat(dest_dir, &statbuf) == 0)
	// 	// {
	// 	// 	printf("found\n");
	// 	// 	break ;
	// 	// }
	// 	// printf("%s\n", dest_dir);
	// 	free(dest_dir);
	// 	i++;
	// }
}

int	searcher(t_data *data)
{
	int			i;
	t_parsing	*parsing;
	t_token_id	*token;
	t_searcher	srch;

	parsing = &data->s_tokens;
	ft_memset(&srch, 0, sizeof(t_searcher));
	i = 0;
	while (i < parsing->tk_nbr)
	{
		token = &parsing->tk_lst[i];
		if (token->token_type == VARIABLE || token->token_type == WEAK_WORD)
			if (!search_variables(token, &srch))
				return (0);
		if (token->token_type == EXIT_STS)
			token->translated_tk = ft_strdup("exit_status(do do later)");
		if (token->token_type == WORD)
			search_functions(data, token);
		i++;
	}
	return (1);
}
