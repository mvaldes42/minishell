/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:37 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/28 15:25:26 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

int	redir_case_general(char **dup, int count, char r_type, char other_r)
{
	char	*error_str;

	error_str = "error: wrong redirection symbol\n";
	*dup += 1;
	if (**dup == other_r)
	{
		printf("%s", error_str);
		return (0);
	}
	else if (**dup == r_type)
		*dup += 1;
	if (**dup == r_type || **dup == other_r)
	{
		printf("%s", error_str);
		return (0);
	}
	else
		count += 1;
	return (count);
}

int	quotes_case_general(char **dup, int count, char q_type)
{
	*dup += 1;
	while (**dup != q_type && **dup != '\0')
		*dup += 1;
	if (**dup == '\0')
	{
		printf("error: missing quote\n");
		return (0);
	}
	count++;
	*dup += 1;
	return (count);
}

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
		printf("| %-*s | %-13s |\n", max_len, \
		lx->tk_lst[i].token_ptr, tk_t_name[lx->tk_lst[i].token_type]);
		while (j < max_len + 13 + 7)
		{
			printf("-");
			j++;
		}
		printf("\n");
		i++;
	}
}
