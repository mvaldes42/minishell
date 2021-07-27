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

#include "../minishell.h"
#include "../utils/general_utils.h"

// echo -n bonjour|echo cool' $HOME top '" $HOME    super'$LANG' "
// echo " $HOME    super'$LANG' "

static	int	count_variables(char *str)
{
	int	i;
	int	var_nbr;

	i = -1;
	var_nbr = 0;
	while (str[++i])
	{
		if (str[i] == VAR)
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
		if (str[i] == VAR)
		{
			start = i;
			srch->o_var_len[j] = 0;
			while (str[i++] && str[i] != VAR && str[i] != ' ' && \
			str[i] != '?' && str[i] != '\'' && str[i] != '\"')
				srch->o_var_len[j] += 1;
			srch->tot_o_len += srch->o_var_len[j];
			srch->var_name[j] = ft_substr(str, start, i - start);
			j += 1;
		}
	}
}

static int	translated_var_length(t_searcher *srch)
{
	int		i;

	srch->var_translated = malloc(sizeof(char **) * (srch->nbr_var + 1));
	srch->t_var_len = malloc(sizeof(size_t *) * (srch->nbr_var + 1));
	i = 0;
	while (i < srch->nbr_var)
	{
		srch->var_translated[i] = getenv(++srch->var_name[i]);
		if (srch->var_translated[i] == NULL)
		{
			printf("\n");
			return (0);
		}
		srch->t_var_len[i] = ft_strlen(srch->var_translated[i]);
		srch->tot_t_len += srch->t_var_len[i];
		printf("srch->var_name[i] = %s, srch->var_translated[i] = %s\n", \
		srch->var_name[i], srch->var_translated[i]);
		i++;
	}
	return (1);
}

static int	weak_word_search(t_token_id *token, t_searcher *srch)
{
	char	*o_str;
	int		i;

	i = 0;
	o_str = ft_strdup(token->token_ptr);
	srch->nbr_var = count_variables(o_str);
	original_var_length(o_str, srch);
	if (!translated_var_length(srch))
		return (0);
	srch->t_token_len = ft_strlen(o_str) - srch->tot_o_len + srch->tot_t_len;
	printf("srch->t_token_len = %zu\n", srch->t_token_len);
	token->translated_tk = malloc(sizeof(char *) * (1 + srch->t_token_len));
	free(srch->o_var_len);
	free(srch->t_var_len);
	i = 0;
	// while (i < srch->nbr_var)
	// {
	// 	free(srch->var_name[i]);
	// 	i++;
	// }
	free(srch->var_name);
	free(srch->var_translated);
	return (1);
}

static int	search_variables(t_token_id *token, t_searcher *srch)
{
	char	*translated_str;

	translated_str = ft_strdup(token->token_ptr);
	if (token->token_type == VARIABLE)
	{
		translated_str++;
		token->translated_tk = getenv(translated_str);
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
	i = 0;
	while (i < parsing->tk_nbr)
	{
		token = &parsing->tk_lst[i];
		if (token->token_type == VARIABLE || token->token_type == WEAK_WORD)
			if (!search_variables(token, &srch))
				return (0);
		i++;
	}
	return (1);
}
