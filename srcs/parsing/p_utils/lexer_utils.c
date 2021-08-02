/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 15:23:04 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/02 14:20:55 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

void	print_lexer_tab(t_parsing	*lx)
{
	int			i;
	int			j;
	int			max_len;
	const char	*tk_t_name[] = {"undefined", "WORD", "PIPE", "VARIABLE", \
	"REDIR_OUT", "REDIR_IN", "READ_IN", "REDIR_OUT_A", "EXIT_STATUS", \
	"WEAK_WORD", "STRONG_WORD"};

	i = 0;
	max_len = 0;
	while (i < lx->tk_nbr && lx->tks[i].ptr)
	{
		if (max_len < (int)ft_strlen(lx->tks[i].ptr))
			max_len = (int)ft_strlen(lx->tks[i].ptr);
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
	while (i < lx->tk_nbr && lx->tks[i].ptr)
	{
		j = 0;
		printf("| %-*s | %-13s |\n", max_len, \
		lx->tks[i].ptr, tk_t_name[lx->tks[i].type]);
		while (j < max_len + 13 + 7)
		{
			printf("-");
			j++;
		}
		printf("\n");
		i++;
	}
}
