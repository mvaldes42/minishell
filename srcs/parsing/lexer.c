/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:46:01 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/13 10:48:05 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_utils/parsing_utils.h"
#include "../minishell.h"

static char	**scanning_tokens(t_parsing *lx, char *line)
{
	char	**unspec_token;

	unspec_token = NULL;
	lx->tk_nbr = token_count(line);
	if (lx->tk_nbr == 0)
		return (NULL);
	unspec_token = token_split(line, lx->tk_nbr);
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

static void	evaluating_tokens(t_parsing *lx, char **unspec_token)
{
	int	i;

	i = -1;
	while (++i < lx->tk_nbr)
	{
		ft_memset(&lx->tks[i], 0, sizeof(lx->tks[i]));
		lx->tks[i].type = WORD;
		lx->tks[i].redir = 0;
		lx->tks[i].ptr = ft_strdup(unspec_token[i]);
		if (ft_strlen(unspec_token[i]) == 1 && unspec_token[i][0] == PIPE_C)
			lx->tks[i].type = PIPE;
		else if (ft_strlen(unspec_token[i]) == 2)
			eval_double_char(lx, unspec_token, i);
		else if (unspec_token[i][0] == R_IN)
			lx->tks[i].type = REDIR_IN;
		else if (unspec_token[i][0] == R_OUT)
			lx->tks[i].type = REDIR_OUT;
		if (lx->tks[i].type == REDIR_OUT_A || lx->tks[i].type == REDIR_IN \
		|| lx->tks[i].type == REDIR_OUT || lx->tks[i].type == READ_IN)
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
	ft_memset(lx->tks, 0, sizeof(t_token) * (data->pars.tk_nbr + 1));
	evaluating_tokens(lx, unspec_token);
	i = 0;
	while (i < lx->tk_nbr)
		ft_free_str(&unspec_token[i++]);
	ft_free_str(unspec_token);
	return (1);
}
