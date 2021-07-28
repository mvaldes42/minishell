/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 21:19:44 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/28 15:36:57 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"

// echo -n bonjour|echo cool' $HOME top '" $HOME    super'$LANG' "
// echo " $HOME    super'$LANG' "

static void	print_parsing_tab(t_data *data)
{
	t_parsing	*lx;
	int			i;
	int			j;
	int			max_len;
	char		*translated_word;
	const char	*tk_t_name[] = {"undefined", "WORD", "PIPE", "VARIABLE", \
	"REDIR_OUT", "REDIR_IN", "READ_IN", "REDIR_OUT_A", "EXIT_STATUS", \
	"WEAK_WORD", "STRONG_WORD"};

	lx = &data->s_tokens;
	i = 0;
	max_len = 0;
	while (i < lx->tk_nbr && lx->tk_lst[i].token_ptr)
	{
		if (max_len < (int)ft_strlen(lx->tk_lst[i].token_ptr))
			max_len = (int)ft_strlen(lx->tk_lst[i].token_ptr);
		i++;
	}
	i = 0;
	j = 0;
	while (j < max_len + 13 + 7)
	{
		printf("-");
		j++;
	}
	printf("\n");
	while (i < lx->tk_nbr && lx->tk_lst[i].token_ptr)
	{
		j = 0;
		translated_word = NULL;
		if (lx->tk_lst[i].token_type == VARIABLE)
			translated_word = ft_strdup(lx->tk_lst[i].translated_var);
		else if (lx->tk_lst[i].token_type == WEAK_WORD)
			translated_word = ft_strdup(lx->tk_lst[i].translated_tk);
		printf("| %-*s | %-13s | %s\n", max_len, \
		lx->tk_lst[i].token_ptr, \
		tk_t_name[lx->tk_lst[i].token_type], translated_word);
		while (j < max_len + 13 + 7)
		{
			printf("-");
			j++;
		}
		printf("\n");
		i++;
	}
}

int	parsing(t_data *data, char *line)
{
	if (!lexer(data, line))
		return (0);
	searcher(data);
	print_parsing_tab(data);
	return (1);
}
