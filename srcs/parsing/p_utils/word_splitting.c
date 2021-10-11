/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_splitting.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:28:28 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/11 16:01:14 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static void	create_new_tk(t_token *tmp_tks, t_exp_var *exp, int *j, int *i)
{
	int		tk_nbr;
	int		word_char;
	int		k;
	int		start;
	int		var;
	int		s;
	char	**split;

	(void)tmp_tks;
	(void)j;
	split = malloc(sizeof(char **) * (exp->nbr_splits + 1));
	tk_nbr = 0;
	word_char = 0;
	start = word_char;
	var = 0;
	printf("exp->nbr_splits : %d\n", exp->nbr_splits);
	s = 0;
	while (exp->tmp_modif_word[word_char])
	{
		while (var < exp->nbr_var)
		{
			while (exp->spot_to_split_var[var][s])
			{
				// printf("exp->spot_to_split_var[var : %d][s: %d] : %d\n", var, s, exp->spot_to_split_var[var][s]);
				// printf("exp->tmp_modif_word[%d != %d] : %c\n", word_char, exp->spot_to_split_var[var][s], exp->tmp_modif_word[word_char]);
				if (word_char == exp->spot_to_split_var[var][s])
				{
					split[tk_nbr] = ft_substr(exp->tmp_modif_word, start, word_char - start);
					// printf("split[%d]: <%s>\n", tk_nbr, split[tk_nbr]);
					// word_char++;
					start = word_char + 1;
					s++;
					tk_nbr++;
				}
				word_char++;
			}
			s = 0;
			var++;
		}
		if (word_char == (int)ft_strlen(exp->tmp_modif_word) - 1)
		{
			split[tk_nbr] = ft_substr(exp->tmp_modif_word, start, word_char + 1 - start);
			// printf("split[%d]: <%s>\n", tk_nbr, split[tk_nbr]);
		}
		word_char++;
	}
	k = 0;
	while (k <= exp->nbr_splits)
	{
		ft_memset(&tmp_tks[*j], 0, sizeof(t_token));
		tmp_tks[*j].type = WORD;
		tmp_tks[*j].ptr = ft_strdup(split[k]);
		// tmp_tks[*j].ptr = ft_strdup("ptr");
		tmp_tks[*j].modif_word = ft_strdup(split[k]);
		// tmp_tks[*j].modif_word = ft_strdup("modif");
		printf("%d: <%s>\n", k, split[k]);
		(*j)++;
		k++;
	}
	// free_split(split);
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

static int	reattribute_tokens(t_data *d, t_exp_var *exp, int tk_to_add)
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
	while (i < d->pars.tk_nbr && j < d->pars.tk_nbr + tk_to_add)
	{
		// printf("d->pars.tks[%d].flag_split : %d\n", i, d->pars.tks[i].flag_split);
		if (d->pars.tks[i].flag_split)
			create_new_tk(tmp_tokens, exp, &j, &i);
		else if (!d->pars.tks[i].flag_split)
			cp_tk_to_temp(tmp_tokens, &d->pars.tks[i], &j, &i);
	}
	tmp_tokens[j].modif_word = NULL;
	tmp_tokens[j].ptr = NULL;
	free(d->pars.tks);
	d->pars.tks = tmp_tokens;
	return (1);
}

int	word_splitting(t_data *d, t_token *tk, t_exp_var *exp, int fct_expt)
{
	int		tk_to_add;

	(void)fct_expt;
	tk_to_add = exp->nbr_splits;
	if (tk_to_add > 0)
	{
		reattribute_tokens(d, exp, tk_to_add);
		d->pars.tk_nbr += tk_to_add;
	}
	else
		tk->modif_word = exp->tmp_modif_word;
	return (1);
}
