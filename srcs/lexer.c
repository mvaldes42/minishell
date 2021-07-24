/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:46:01 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/23 22:35:57 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/utils.h"

static char	**scanning_tokens(t_lexer *lx, char *line)
{
	char	**unspec_token;

	lx->tk_nbr = word_count(line, ' ');
	printf("count : %d\n", lx->tk_nbr);
	// unspec_token = malloc(sizeof(char *) * (lx->tk_nbr + 1));
	// unspec_token = ft_split(line, ' ');
	return (unspec_token);
}

//FONCTION EN COURS DE DEV
void	evaluating_tokens(t_lexer *lx, char **unspec_token)
{
	int		i;

	i = 0;
	while (i < lx->tk_nbr)
	{
		lx->tk_lst[i].token_ptr = ft_strdup(unspec_token[i]);
		// if (ft_strlen(unspec_token[i]) == 1 && unspec_token[i][0] == CHAR_PIPE)
		// 	lx->tk_lst[i].token_type = CHAR_PIPE;
		// else if (ft_strlen(unspec_token[i]) == 2)
		// {
		// 	if (ft_strncmp(unspec_token[i], ">>", 2))
		// 		lx->tk_lst[i].token_type = STR_RED_OUT_APP;
		// 	if (ft_strncmp(unspec_token[i], "<<", 2))
		// 		lx->tk_lst[i].token_type = STR_READ_IN;
		// 	if (ft_strncmp(unspec_token[i], "$?", 2))
		// 		lx->tk_lst[i].token_type = STR_EXIT_STAT;
		// }
		// else if (unspec_token[i][0] == CHAR_EXP)
		// 	lx->tk_lst[i].token_type = CHAR_EXP;
		// else if (unspec_token[i][0] == CHAR_EXP)
		// 	lx->tk_lst[i].token_type = CHAR_EXP;
		// else if (is_occu_odd(unspec_token[i], CHAR_SINGLE_QUOTE) == 1)
		printf("token is = %-20s, token type is = %c\n", lx->tk_lst[i].token_ptr, lx->tk_lst[i].token_type);
		i++;
	}
}

int	lexer(t_data *data, char *line, t_lexer *lx)
{
	char	**unspec_token;

	if (char_occu(line, CHAR_SINGLE_QUOTE) % 2 \
		|| char_occu(line, CHAR_DOUBLE_QUOTE) % 2)
		exit_fail(data);
	unspec_token = scanning_tokens(lx, line);
	// lx->tk_lst = (t_token_id *)malloc(sizeof(t_token_id) * \
	// (data->s_tokens.tk_nbr + 1));
	// evaluating_tokens(lx, unspec_token);
	// free(unspec_token);
	return (1);
}
