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

static char	*replace_substr(t_searcher *srch, char *str, int dst_size)
{
	t_var_replace	v;
	int				i;
	int				j;

	i = 0;
	j = 1;
	v.var_nb = 0;
	v.dest = malloc(sizeof(char *) * (dst_size));
	while (i < dst_size - 1 && str[j] != '\0')
	{
		if (str[j] == VAR)
		{
			v.var_size = 0;
			j++;
			while (v.var_size < srch->t_var_len[v.var_nb])
				v.dest[i++] = srch->var_translated[v.var_nb][v.var_size++];
			j += srch->o_var_len[v.var_nb++];
		}
		else
			v.dest[i++] = str[j++];
	}
	v.dest[i] = '\0';
	return (v.dest);
}

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
		i++;
	}
	return (1);
}
