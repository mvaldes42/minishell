/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:28:28 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/20 14:59:04 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static int	count_word_split(t_searcher *srch, int fct_expt)
{
	int		i;
	int		count;
	char	*tmp;
	int		tmp_size;

	i = 0;
	count = 0;
	tmp = srch->tmp_modif_word;
	tmp_size = ft_strlen(tmp);
	while (tmp != NULL && i < tmp_size)
	{
		if (tmp[i] == D_QUOTE)
			while (++i < tmp_size && tmp[i] != D_QUOTE)
				;
		if (tmp[i] == SPACE || tmp[i] == TAB)
			count += 1;
		if (tmp[i] == '=' && fct_expt)
			while (++i < tmp_size)
				;
		i++;
	}
	return (count);
}

static void	create_new_tk(char *mod_word, t_token *tmp_tks, int *j, int *i)
{
	int		k;
	int		nbr_split;
	char	**split;

	k = 0;
	nbr_split = token_count(mod_word);
	split = token_split(mod_word, nbr_split);
	while (k < nbr_split)
	{
		ft_memset(&tmp_tks[*j], 0, sizeof(t_token));
		tmp_tks[*j].type = WORD;
		tmp_tks[*j].ptr = ft_strdup(split[k]);
		tmp_tks[*j].modif_word = ft_strdup(split[k]);
		(*j)++;
		k++;
	}
	free_split(split);
	*i += 1;
}

static void	cp_tk_to_temp(t_token *tmp_tokens, t_token *tk, int *j, int *i)
{
	tmp_tokens[*j].type = tk->type;
	tmp_tokens[*j].ptr = ft_strdup(tk->ptr);
	tmp_tokens[*j].redir = tk->redir;
	tmp_tokens[*j].echo_opt = tk->echo_opt;
	tmp_tokens[*j].flag_split = tk->flag_split;
	tmp_tokens[*j].modif_word = tk->modif_word;
	ft_free_str(&tk->ptr);
	(*j) += 1;
	(*i) += 1;
}

static int	reattribute_tokens(t_data *d, int tk_to_add, char *modif_word)
{
	t_token	*tmp_tokens;
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
		if (d->pars.tks[i].flag_split)
			create_new_tk(modif_word, tmp_tokens, &j, &i);
		else if (!d->pars.tks[i].flag_split)
			cp_tk_to_temp(tmp_tokens, &d->pars.tks[i], &j, &i);
	}
	tmp_tokens[j].modif_word = NULL;
	tmp_tokens[j].ptr = NULL;
	free(d->pars.tks);
	d->pars.tks = tmp_tokens;
	return (1);
}

int	word_splitting(t_data *d, t_token *tk, t_searcher *srch, int fct_expt)
{
	int		tk_to_add;

	tk_to_add = count_word_split(srch, fct_expt);
	if (tk_to_add > 0)
	{
		reattribute_tokens(d, tk_to_add, srch->tmp_modif_word);
		d->pars.tk_nbr += tk_to_add;
	}
	else
		tk->modif_word = srch->tmp_modif_word;
	return (1);
}
