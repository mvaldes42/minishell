/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:46:01 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/31 11:21:53 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"

static char	**scanning_tokens(t_parsing *lx, char *line)
{
	char	**unspec_token;

	unspec_token = NULL;
	lx->tk_nbr = token_count(line, SPACE);
	if (lx->tk_nbr == 0)
		return (NULL);
	unspec_token = token_split(line, SPACE);
	return (unspec_token);
}

static void	eval_double_char(t_parsing *lx, char **unspec_token, int i)
{
	if (!ft_strncmp(unspec_token[i], ">>", 2))
		lx->tks[i].type = REDIR_OUT_A;
	if (!ft_strncmp(unspec_token[i], "<<", 2))
		lx->tks[i].type = READ_IN;
	if (!ft_strncmp(unspec_token[i], "$?", 2))
		lx->tks[i].type = EXIT_STS;
}

static int	is_redir(t_parsing *lx, int i)
{
	if (lx->tks[i].type == REDIR_OUT_A || lx->tks[i].type == REDIR_IN \
	|| lx->tks[i].type == REDIR_OUT || lx->tks[i].type == READ_IN)
		return (1);
	return (0);
}

static void	evaluating_tokens(t_parsing *lx, char **unspec_token)
{
	int	i;

	i = -1;
	while (++i < lx->tk_nbr)
	{
		lx->tks[i].type = WORD;
		lx->tks[i].redir = 0;
		lx->tks[i].ptr = ft_strdup(unspec_token[i]);
		if (ft_strlen(unspec_token[i]) == 1 && unspec_token[i][0] == PIPE_C)
			lx->tks[i].type = PIPE;
		else if (ft_strlen(unspec_token[i]) == 2)
			eval_double_char(lx, unspec_token, i);
		else if (unspec_token[i][0] == VAR)
			lx->tks[i].type = VARIABLE;
		else if (unspec_token[i][0] == S_QUOTE)
			lx->tks[i].type = STRONG_WORD;
		else if (unspec_token[i][0] == D_QUOTE)
			lx->tks[i].type = WEAK_WORD;
		else if (unspec_token[i][0] == R_IN)
			lx->tks[i].type = REDIR_IN;
		else if (unspec_token[i][0] == R_OUT)
			lx->tks[i].type = REDIR_OUT;
		if (is_redir(lx, i))
			lx->tks[i].redir = 1;
	}
}

int	lexer(t_data *data, char *line)
{
	char		**unspec_token;
	t_parsing	*lx;
	int			i;

	lx = &data->pars;
	ft_memset(lx, 0, sizeof(t_parsing));
	unspec_token = scanning_tokens(lx, line);
	if (unspec_token == NULL)
		return (0);
	lx->tks = (t_token *)malloc(sizeof(t_token) * (data->pars.tk_nbr + 1));
	evaluating_tokens(lx, unspec_token);
	i = 0;
	while (i < lx->tk_nbr)
		ft_free_str(&unspec_token[i++]);
	ft_free_str(unspec_token);
	return (1);
}
