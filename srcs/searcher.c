/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:35:55 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/26 13:40:28 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/general_utils.h"

// echo -n bonjour|echo cool' $HOME top '" $HOME    super'$LANG' "
static size_t	*var_length(char *str)
{
	size_t	*var_len;
	int		i;
	int		var_nbr;

	i = -1;
	var_nbr = 0;
	while (str[++i])
	{
		if (str[i] == CHAR_EXP)
			var_nbr++;
	}
	printf("var_nbr = %d\n", var_nbr);
	var_len = malloc(sizeof(size_t) * (var_nbr + 1));
	i = 0;
	while (str[i])
	{
		if (str[i] == CHAR_EXP)
		{
			while
		}
		i++;
	}
	return (var_len);
}

static char	*weak_word_search(t_token_id *token)
{
	char	*orgn_str;
	size_t	*var_len;
	int		i;

	i = 0;
	orgn_str = ft_strdup(token->token_ptr);
	var_len = var_length(orgn_str);
	// while (*orgn_str)
	// {
	// 	if (*orgn_str == CHAR_EXP)
	// 	{
	// 		var_len = 0;
	// 		while (*orgn_str != CHAR_EXP || \
	// 		*orgn_str != ' ' | *orgn_str != '?')
	// 		{
	// 			var_len++;
	// 			orgn_str++;
	// 		}
	// 	}
	// 	orgn_str++;
	// }
	token->translated_tk = ft_strdup(token->token_ptr);
	return (token->translated_tk);
}

static void	search_variables(t_token_id *token)
{
	char	*translated_str;

	translated_str = ft_strdup(token->token_ptr);
	if (token->token_type == VARIABLE)
	{
		translated_str++;
		token->translated_tk = getenv(translated_str);
	}
	else if (token->token_type == WEAK_WORD)
		token->translated_tk = weak_word_search(token);
	printf("token->token_ptr =%s\n", token->translated_tk);
}

int	searcher(t_data *data)
{
	int			i;
	t_parsing	*parsing;
	t_token_id	*token;

	parsing = &data->s_tokens;
	i = 0;
	while (i < parsing->tk_nbr)
	{
		token = &parsing->tk_lst[i];
		if (token->token_type == VARIABLE || token->token_type == WEAK_WORD)
			search_variables(token);
		i++;
	}
	return (1);
}
