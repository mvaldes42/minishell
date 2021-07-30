/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:46:01 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/30 15:32:35 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"

static char	**scanning_tokens(t_parsing *lx, char *line)
{
	char	**unspec_token;

	lx->tk_nbr = token_count(line, SPACE);
	if (lx->tk_nbr == 0)
		return (NULL);
	unspec_token = token_split(line, SPACE);
	return (unspec_token);
}

static void	eval_double_char(t_parsing *lx, char **unspec_token, int i)
{
	if (!ft_strncmp(unspec_token[i], ">>", 2))
		lx->tk_lst[i].token_type = REDIR_OUT_A;
	if (!ft_strncmp(unspec_token[i], "<<", 2))
		lx->tk_lst[i].token_type = REDIR_IN;
	if (!ft_strncmp(unspec_token[i], "$?", 2))
		lx->tk_lst[i].token_type = EXIT_STS;
}

static void	evaluating_tokens(t_parsing *lx, char **unspec_token)
{
	int	i;

	i = 0;
	while (i < lx->tk_nbr)
	{
		lx->tk_lst[i].token_type = WORD;
		lx->tk_lst[i].token_ptr = ft_strdup(unspec_token[i]);
		if (ft_strlen(unspec_token[i]) == 1 && unspec_token[i][0] == PIPE_C)
			lx->tk_lst[i].token_type = PIPE;
		else if (ft_strlen(unspec_token[i]) == 2)
			eval_double_char(lx, unspec_token, i);
		else if (unspec_token[i][0] == VAR)
			lx->tk_lst[i].token_type = VARIABLE;
		else if (unspec_token[i][0] == S_QUOTE)
			lx->tk_lst[i].token_type = STRONG_WORD;
		else if (unspec_token[i][0] == D_QUOTE)
			lx->tk_lst[i].token_type = WEAK_WORD;
		else if (unspec_token[i][0] == R_IN)
			lx->tk_lst[i].token_type = REDIR_IN;
		else if (unspec_token[i][0] == R_OUT)
			lx->tk_lst[i].token_type = REDIR_OUT;
		i++;
	}
}

int	lexer(t_data *data, char *line)
{
	char		**unspec_token;
	t_parsing	*lx;
	int			i;

	lx = &data->parsing;
	ft_memset(lx, 0, sizeof(t_parsing));
	unspec_token = scanning_tokens(lx, line);
	if (unspec_token == NULL)
		return (0);
	lx->tk_lst = (t_token_id *)malloc(sizeof(t_token_id) * \
	(data->parsing.tk_nbr + 1));
	evaluating_tokens(lx, unspec_token);
	i = 0;
	while (i < lx->tk_nbr)
		free(unspec_token[i++]);
	free(unspec_token);
	return (1);
}
