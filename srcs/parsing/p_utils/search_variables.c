/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:42:09 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 16:45:50 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static void	original_var_length(char *str, t_exp_var *exp)
{
	int		j;
	int		i;
	int		start;

	i = 0;
	j = 0;
	exp->o_var_len = malloc(sizeof(size_t) * (exp->nbr_var + 1));
	exp->var_name = malloc(sizeof(char **) * (exp->nbr_var + 1));
	while (str[i] != '\0' && j < exp->nbr_var)
	{
		if (str[i] == VAR)
		{
			start = i;
			exp->o_var_len[j] = 1;
			while (str[++i] && str[i] != VAR && str[i] != SPACE && \
			str[i] != TAB && str[i] != S_QUOTE && str[i] != D_QUOTE && \
			str[i] != '=' && str[i] != '/')
				exp->o_var_len[j] += 1;
			exp->tot_o_len += exp->o_var_len[j];
			exp->var_name[j] = ft_substr(str, start, i - start);
			j += 1;
		}
		else
			i++;
	}
}

static int	translated_var_length(t_exp_var *exp, t_token *tk, char **environ)
{
	int		i;

	(void)tk;
	errno = VAR_NOT_FOUND;
	exp->var_trans = malloc(sizeof(char *) * (exp->nbr_var + 1));
	exp->t_var_len = malloc(sizeof(size_t) * (exp->nbr_var + 1));
	exp->current_o_len = 0;
	i = 0;
	while (i < exp->nbr_var)
	{
		if (ft_strncmp(exp->var_name[i], "$?", 2) == 0)
			exp->var_trans[i] = ft_strdup("exit_status(do do later)");
		else
		{
			exp->var_trans[i] = ft_getenv(++exp->var_name[i], environ);
			--exp->var_name[i];
		}
		exp->t_var_len[i] = ft_strlen(exp->var_trans[i]);
		exp->tot_t_len += exp->t_var_len[i];
		exp->current_o_len += exp->o_var_len[i];
		i++;
	}
	return (1);
}

int	search_variables(t_data *d, int i, char **environ)
{
	int			fct_expt;
	t_token		*tk;
	t_exp_var	exp;

	tk = &d->pars.tks[i];
	ft_memset(&exp, 0, sizeof(exp));
	fct_expt = 0;
	if (i > 0 && d->pars.tks[i - 1].type == BUILTIN && \
	ft_str_in_str("export", d->pars.tks[i - 1].ptr))
		fct_expt = 1;
	exp.nbr_var = count_variables(tk, tk->ptr, fct_expt);
	if (exp.nbr_var == 0)
		tk->modif_word = ft_strdup(tk->ptr);
	else
	{
		original_var_length(tk->ptr, &exp);
		translated_var_length(&exp, tk, environ);
		exp.t_token_len = ft_strlen(tk->ptr) - exp.tot_o_len + exp.tot_t_len;
		exp.tmp_modif_word = rplc_substr_init(&exp, tk->ptr, exp.t_token_len);
		// printf("exp->tmp_modif_word : %s\n", exp.tmp_modif_word);
		tk->modif_word = exp.tmp_modif_word;
		free_expand_struct(&exp);
	}
	return (1);
}
