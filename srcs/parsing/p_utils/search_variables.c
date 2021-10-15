/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:42:09 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/15 12:09:26 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static void	if_var_case(t_exp_var *exp, char *str, int *i, int *j)
{
	int	start;

	start = *i;
	exp->o_var_len[*j] = 1;
	while (str[++(*i)] && str[*i] != VAR && str[*i] != SPACE && \
	str[*i] != TAB && str[*i] != S_QUOTE && str[*i] != D_QUOTE \
	&& str[*i] != '=' && str[*i] != '/')
	{
		// printf("str[%d]: %c\n", *i, str[*i]);
		if (exp->o_var_len[*j] == 1 && str[*i] >= '1' && str[*i] <= '9')
		{
			exp->o_var_len[*j] += 1;
			break ;
		}
		exp->o_var_len[*j] += 1;
	}
	// printf("str[%d]: %c\n", *i, str[*i]);
	// if (exp->o_var_len[*j] == 1 && str[*i] >= '1' && str[*i] <= '9')
	// {
	// 	printf("hello\n");
	// 	exp->o_var_len[*j] += 1;
	// }
	exp->tot_o_len += exp->o_var_len[*j];
	exp->var_name[*j] = ft_substr(str, start, *i - start);
	(*j)++;
}

static void	original_var_length(char *str, t_exp_var *exp)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (i < (int)ft_strlen(str) && j < exp->nbr_var)
	{
		if (str[i] == S_QUOTE)
			while (++i < (int)ft_strlen(str) && str[i] != S_QUOTE)
				;
		else if (str[i] == D_QUOTE)
		{
			i++;
			while (i < (int)ft_strlen(str) && str[i] != D_QUOTE)
			{
				if (str[i] == VAR)
					if_var_case(exp, str, &i, &j);
				if (str[i] == D_QUOTE)
					break ;
				else if (str[i] != VAR)
					i++;
			}
		}
		if (i < (int)ft_strlen(str) && str[i] == VAR)
			if_var_case(exp, str, &i, &j);
		else if (i < (int)ft_strlen(str))
			i++;
	}
}

static int	translated_var_length(t_exp_var *exp, t_token *tk, char **environ)
{
	int		i;

	(void)tk;
	errno = VAR_NOT_FOUND;
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
		if (exp->o_var_len[i] == 1 && exp->t_var_len[i] == 0)
			exp->t_var_len[i] = 1;
		// printf("exp->var_trans[i] : %s, exp->t_var_len[i] : %zu\n", exp->var_trans[i], exp->t_var_len[i]);
		exp->tot_t_len += exp->t_var_len[i];
		exp->current_o_len += exp->o_var_len[i];
		i++;
	}
	return (1);
}

int	init_search_variable(t_data *d, t_exp_var *exp, t_token *tk, int i)
{
	int		fct_expt;

	ft_memset(exp, 0, sizeof(*exp));
	fct_expt = 0;
	if (i > 0 && d->pars.tks[i - 1].type == BUILTIN && \
	ft_str_in_str("export", d->pars.tks[i - 1].ptr))
		fct_expt = 1;
	exp->nbr_var = count_variables(tk, tk->ptr, fct_expt);
	return (1);
}

int	search_variables(t_data *d, int i, char **environ)
{
	t_token		*tk;
	t_exp_var	exp;

	tk = &d->pars.tks[i];
	if (!init_search_variable(d, &exp, tk, i))
		return (0);
	if (exp.nbr_var == 0)
		tk->modif_word = ft_strdup(tk->ptr);
	else
	{
		exp.o_var_len = malloc(sizeof(size_t) * (exp.nbr_var + 1));
		exp.var_name = malloc(sizeof(char **) * (exp.nbr_var + 1));
		exp.var_trans = malloc(sizeof(char *) * (exp.nbr_var + 1));
		exp.t_var_len = malloc(sizeof(size_t) * (exp.nbr_var + 1));
		original_var_length(tk->ptr, &exp);
		translated_var_length(&exp, tk, environ);
		exp.t_token_len = ft_strlen(tk->ptr) - exp.tot_o_len + exp.tot_t_len;
		// printf("ft_strlen(tk->ptr): %zu - exp.tot_o_len: %zu +  exp.tot_t_len: %zu\n", ft_strlen(tk->ptr), exp.tot_o_len, exp.tot_t_len);
		exp.tmp_modif_word = rplc_substr_init(&exp, tk->ptr, exp.t_token_len);
		tk->modif_word = exp.tmp_modif_word;
		free_expand_struct(&exp);
	}
	return (1);
}
