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

#include "minishell.h"
#include "utils/general_utils.h"

// echo -n bonjour|echo cool' $HOME top '" $HOME    super'$LANG' "

static	int	nbr_var(char *str)
{
	int	i;
	int	var_nbr;

	i = -1;
	var_nbr = 0;
	while (str[++i])
	{
		if (str[i] == CHAR_EXP)
			var_nbr++;
	}
	return (var_nbr);
}

static void	original_var_length(char *str, t_searcher *srch)
{
	int		j;
	int		i;
	int		start;

	i = 0;
	j = 0;
	srch->o_var_len = malloc(sizeof(size_t) * (srch->nbr_var + 1));
	srch->var_name = malloc(sizeof(char **) * (srch->nbr_var + 1));
	while (str[i++] && j < srch->nbr_var)
	{
		if (str[i] == CHAR_EXP)
		{
			start = i;
			srch->o_var_len[j] = 0;
			while (str[i++] && str[i] != CHAR_EXP && str[i] != ' ' && \
			str[i] != '?' && str[i] != '\'' && str[i] != '\"')
				srch->o_var_len[j] += 1;
			srch->var_name[j] = ft_substr(str, start, i - start);
			j += 1;
		}
	}
}

static void	translated_var_length(t_searcher *srch)
{
	int		i;

	srch->var_translated = malloc(sizeof(char **) * (srch->nbr_var + 1));
	srch->t_var_len = malloc(sizeof(size_t *) * (srch->nbr_var + 1));
	i = 0;
	while (i < srch->nbr_var)
	{
		srch->var_translated[i] = getenv(++srch->var_name[i]);
		if (srch->var_translated[i] == NULL)
			exit(1);
		srch->t_var_len[i] = ft_strlen(srch->var_translated[i]);
		printf("srch->var_name[i] = %s, srch->var_translated[i] = %s\n", \
		srch->var_name[i], srch->var_translated[i]);
		i++;
	}
}

static char	*weak_word_search(t_token_id *token, t_searcher *srch)
{
	char	*o_str;
	int		i;

	i = 0;
	o_str = ft_strdup(token->token_ptr);
	srch->nbr_var = nbr_var(o_str);
	original_var_length(o_str, srch);
	translated_var_length(srch);
	token->translated_tk = ft_strdup(token->token_ptr);
	return (token->translated_tk);
}

static void	search_variables(t_token_id *token, t_searcher *srch)
{
	char	*translated_str;

	translated_str = ft_strdup(token->token_ptr);
	if (token->token_type == VARIABLE)
	{
		translated_str++;
		token->translated_tk = getenv(translated_str);
	}
	else if (token->token_type == WEAK_WORD)
		token->translated_tk = weak_word_search(token, srch);
}

int	searcher(t_data *data)
{
	int			i;
	t_parsing	*parsing;
	t_token_id	*token;
	t_searcher	*srch;

	parsing = &data->s_tokens;
	srch = &data->s_tokens.searcher;
	i = 0;
	while (i < parsing->tk_nbr)
	{
		token = &parsing->tk_lst[i];
		if (token->token_type == VARIABLE || token->token_type == WEAK_WORD)
			search_variables(token, srch);
		i++;
	}
	return (1);
}
