/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:46:01 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/02 14:27:52 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/utils.h"

char	**take_tokens_out(t_data *data, t_lexer *lx, char *line, char *sep)
{
	char	**unspec_token;
	char	*ptr;
	char	*line_bis;
	int		i;

	i = 0;
	line_bis = ft_strdup(line);
	lx->tk_nbr = sep_token_count(data, line_bis, sep);
	printf("count : %d\n", lx->tk_nbr);
	unspec_token = (char **)malloc(sizeof(char *) * (lx->tk_nbr + 1));
	// ptr = ft_strtok(line_bis, sep);
	// while (ptr != NULL && i < lx->tk_nbr)
	// {
	// 	unspec_token[i] = ptr;
	// 	printf(">%s<\n", unspec_token[i]);
	// 	i++;
	// 	ptr = ft_strtok(NULL, sep);
	// }
	// ft_strtok_spec(line_bis, sep);
	free(line_bis);
	return (unspec_token);
}

// void	scanning(t_lexer *lx, char **unspec_token)
// {
// 	int		i;

// 	i = 0;
// 	while (i < lx->tk_nbr)
// 	{
// 		lx->tk_lst[i].token_ptr = ft_strdup(unspec_token[i]);
// 		if (ft_strlen(unspec_token[i]) == 1 && unspec_token[i][0] == CHAR_PIPE)
// 			lx->tk_lst[i].token_type = CHAR_PIPE;
// 		else if (ft_strlen(unspec_token[i]) == 2)
// 		{
// 			if (ft_strncmp(unspec_token[i], ">>", 2))
// 				lx->tk_lst[i].token_type = STR_RED_OUT_APP;
// 			if (ft_strncmp(unspec_token[i], "<<", 2))
// 				lx->tk_lst[i].token_type = STR_READ_IN;
// 			if (ft_strncmp(unspec_token[i], "$?", 2))
// 				lx->tk_lst[i].token_type = STR_EXIT_STAT;
// 		}
// 		else if (unspec_token[i][0] == CHAR_EXP)
// 			lx->tk_lst[i].token_type = CHAR_EXP;
// 		else if (unspec_token[i][0] == CHAR_EXP)
// 			lx->tk_lst[i].token_type = CHAR_EXP;
// 		// else if (is_occu_odd(unspec_token[i], CHAR_SINGLE_QUOTE) == 1)
// 		printf("%s && %c\n", lx->tk_lst[i].token_ptr, lx->tk_lst[i].token_type);
// 		i++;
// 	}
// }

int	lexer(t_data *data, char *line, t_lexer *lx)
{
	char	**unspec_token;
	char	*sep;

	sep = " \'\"|<>$";
	if (char_occu(line, CHAR_SINGLE_QUOTE) % 2 \
		|| char_occu(line, CHAR_DOUBLE_QUOTE) % 2)
		exit_fail(data);
	unspec_token = take_tokens_out(data, lx, line, sep);
	// lx->tk_lst = (t_token_id *)malloc((sizeof(char *) * (lx->tk_nbr + 1)) + \
	// (sizeof(int) * (lx->tk_nbr + 1)));
	// scanning(lx, unspec_token);
	free(unspec_token);
	return (1);
}
