/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:46:01 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/27 11:59:38 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils/general_utils.h"

static void	print_lexer_tab(t_parsing	*lx)
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

static char	**scanning_tokens(t_parsing *lx, char *line)
{
	char	**unspec_token;

	lx->tk_nbr = token_count(line, SPACE);
	if (lx->tk_nbr == 0)
		return (NULL);
	printf("count : %d\n", lx->tk_nbr);
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
	int			i;

	i = 0;
	while (i < lx->tk_nbr)
	{
		lx->tk_lst[i].token_type = 0;
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
		else if (lx->tk_lst[i].token_type == 0)
			lx->tk_lst[i].token_type = WORD;
		i++;
	}
}

int	lexer(t_data *data, char *line)
{
	char		**unspec_token;
	t_parsing	*lx;
	int			i;

	lx = &data->s_tokens;
	ft_memset(lx, 0, sizeof(t_parsing));
	unspec_token = scanning_tokens(lx, line);
	if (unspec_token == NULL)
		return (0);
	lx->tk_lst = (t_token_id *)malloc(sizeof(t_token_id) * \
	(data->s_tokens.tk_nbr + 1));
	evaluating_tokens(lx, unspec_token);
	i = 0;
	while (i < lx->tk_nbr)
		free(unspec_token[i++]);
	free(unspec_token);
	print_lexer_tab(lx);
	return (1);
}
