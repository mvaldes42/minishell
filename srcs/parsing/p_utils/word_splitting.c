/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:28:28 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/16 16:39:19 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static int	count_word_split(t_searcher *srch)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	tmp = srch->tmp_modif_word;
	while (tmp != NULL && tmp[i])
	{
		if (tmp[i] == D_QUOTE)
			while (tmp[++i] && tmp[i] != D_QUOTE)
				;
		if (tmp[i] == SPACE || tmp[i] == TAB)
			count += 1;
		i++;
	}
	return (count);
}

static t_token	create_new_token(char *modif_word, t_token tmp_tokens)
{
	int		k;
	int		nbr_split;
	char	**split;

	k = 0;
	nbr_split = token_count(modif_word);
	split = token_split(modif_word, nbr_split);
	while (k < nbr_split)
	{
		ft_memset(&tmp_tokens[j], 0, sizeof(t_token));
		tmp_tokens[j].type = WORD;
		tmp_tokens[j].ptr = ft_strdup(split[k]);
		tmp_tokens[j].modif_word = ft_strdup(split[k]);
		j++;
		k++;
	}
	free_split(split);
	return (tmp_tokens);
}

static int	reattribute_tokens(t_data *d, int tk_to_add, char *modif_word)
{
	t_token	*tmp_tokens;
	t_token	tk;
	int		i;
	int		j;

	tmp_tokens = malloc(sizeof(t_token) * (d->pars.tk_nbr + tk_to_add + 1));
	ft_memset(tmp_tokens, 0, sizeof(tmp_tokens));
	if (!(tmp_tokens))
		return (0);
	i = 0;
	j = 0;
	while (i < d->pars.tk_nbr || j < d->pars.tk_nbr + tk_to_add)
	{
		tk = d->pars.tks[i];
		if (tk.flag_split)
		{
			tmp_tokens[j] = create_new_token(j, modif_word, tmp_tokens);
			i++;
		}
		else if (!tk.flag_split)
		{
			tmp_tokens[j].type = tk.type;
			tmp_tokens[j].ptr = ft_strdup(tk.ptr);
			tmp_tokens[j].redir = tk.redir;
			tmp_tokens[j].echo_opt = tk.echo_opt;
			tmp_tokens[j].flag_split = tk.flag_split;
			tmp_tokens[j].modif_word = tk.modif_word;
			ft_free_str(&tk.ptr);
			j++;
			i++;
		}
	}
	tmp_tokens[j].modif_word = NULL;
	tmp_tokens[j].ptr = NULL;
	free(d->pars.tks);
	d->pars.tks = tmp_tokens;
	return (1);
}

int	word_splitting(t_data *d, t_token *tk, t_searcher *srch)
{
	int		tk_to_add;

	tk_to_add = count_word_split(srch);
	if (tk_to_add > 0)
	{
		reattribute_tokens(d, tk_to_add, srch->tmp_modif_word);
		d->pars.tk_nbr += tk_to_add;
	}
	else
		tk->modif_word = srch->tmp_modif_word;
	return (1);
}