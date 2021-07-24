/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:46:01 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/24 20:47:36 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/general_utils.h"

static char	**scanning_tokens(t_lexer *lx, char *line)
{
	char	**unspec_token;

	lx->tk_nbr = token_count(line, ' ');
	if (lx->tk_nbr == 0)
		exit(1);
	printf("count : %d\n", lx->tk_nbr);
	unspec_token = malloc(sizeof(char *) * (lx->tk_nbr + 1));
	unspec_token = token_split(line, ' ');
	return (unspec_token);
}

void	eval_double_char(t_lexer *lx, char **unspec_token, int i)
{
	if (!ft_strncmp(unspec_token[i], ">>", 2))
		lx->tk_lst[i].token_type = REDIR_OUT_A;
	if (!ft_strncmp(unspec_token[i], "<<", 2))
		lx->tk_lst[i].token_type = REDIR_IN;
	if (!ft_strncmp(unspec_token[i], "$?", 2))
		lx->tk_lst[i].token_type = EXIT_STS;
}

void	evaluating_tokens(t_lexer *lx, char **unspec_token)
{
	int			i;

	i = 0;
	while (i < lx->tk_nbr)
	{
		lx->tk_lst[i].token_ptr = ft_strdup(unspec_token[i]);
		if (ft_strlen(unspec_token[i]) == 1 && unspec_token[i][0] == CHAR_PIPE)
			lx->tk_lst[i].token_type = PIPE;
		else if (ft_strlen(unspec_token[i]) == 2)
			eval_double_char(lx, unspec_token, i);
		else if (unspec_token[i][0] == CHAR_EXP)
			lx->tk_lst[i].token_type = VARIABLE;
		else if (unspec_token[i][0] == CHAR_SINGLE_QUOTE)
			lx->tk_lst[i].token_type = STRONG_WORD;
		else if (unspec_token[i][0] == CHAR_DOUBLE_QUOTE)
			lx->tk_lst[i].token_type = WEAK_WORD;
		else if (unspec_token[i][0] == CHAR_RED_IN)
			lx->tk_lst[i].token_type = REDIR_IN;
		else if (unspec_token[i][0] == CHAR_RED_OUT)
			lx->tk_lst[i].token_type = REDIR_OUT;
		if (lx->tk_lst[i].token_type == 0)
			lx->tk_lst[i].token_type = WORD;
		i++;
	}
}

int	lexer(t_data *data, char *line, t_lexer *lx)
{
	char		**unspec_token;
	int			i;
	const char	*tk_t_name[] = {"undefined", "WORD", "PIPE", "VARIABLE", \
	"REDIR_OUT", "REDIR_IN", "READ_IN", "REDIR_OUT_A", "EXIT_STATUS", \
	"WEAK_WORD", "STRONG_WORD"};

	if (char_occu(line, CHAR_SINGLE_QUOTE) % 2 \
		|| char_occu(line, CHAR_DOUBLE_QUOTE) % 2)
		exit_fail(data);
	unspec_token = scanning_tokens(lx, line);
	lx->tk_lst = (t_token_id *)malloc(sizeof(t_token_id) * \
	(data->s_tokens.tk_nbr + 1));
	evaluating_tokens(lx, unspec_token);
	free(unspec_token);
	i = 0;
	while (i < lx->tk_nbr)
	{
		printf("| %-20s | %-13s |\n", \
		lx->tk_lst[i].token_ptr, tk_t_name[lx->tk_lst[i].token_type]);
		printf("----------------------------------------\n");
		i++;
	}
	return (1);
}
