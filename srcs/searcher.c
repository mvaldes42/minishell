/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:35:55 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/24 22:57:18 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/general_utils.h"

static void	search_variables(t_token_id *token)
{
	char	*translated_str;

	translated_str = ft_strdup(token->token_ptr);
	if (token->token_type == VARIABLE)
	{
		translated_str++;
		token->translated_tk = getenv(translated_str);
	}
	// else if (token->token_type == WEAK_WORD)
	// {
	// 	while (*translated_str && *translated_str != CHAR_EXP)
	// 	{
	// 	}
	// }
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
