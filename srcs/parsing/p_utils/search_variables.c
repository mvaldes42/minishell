/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:42:09 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/11 16:09:19 by mvaldes          ###   ########.fr       */
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
	exp->spot_of_var = malloc(sizeof(int) * (exp->nbr_var + 1));
	while (str[i] != '\0' && j < exp->nbr_var)
	{
		if (str[i] == VAR)
		{
			start = i;
			exp->o_var_len[j] = 1;
			exp->spot_of_var[j] = start;
			while (str[++i] && str[i] != VAR && str[i] != SPACE && \
			str[i] != TAB && str[i] != S_QUOTE && str[i] != D_QUOTE)
				exp->o_var_len[j] += 1;
			exp->tot_o_len += exp->o_var_len[j];
			exp->var_name[j] = ft_substr(str, start, i - start);
			j += 1;
		}
		else
			i++;
	}
}

static int	how_many_spaces(char *str)
{
	int	nbr_spaces;
	int	i;

	nbr_spaces = 0;
	i = -1;
	while (str[++i])
		if (str[i] == SPACE || str[i] == TAB)
			nbr_spaces ++;
	return (nbr_spaces);
}

static void	where_to_split(t_exp_var *exp, char *str, int var)
{
	int	i;
	int	j;
	int	nbr_splits;

	nbr_splits = how_many_spaces(exp->var_trans[var]);
	exp->spot_to_split_var[var] = malloc(sizeof(int) * (nbr_splits + 1));
	i = -1;
	j = 0;
	printf("str: %s, nbr_splits: %d\n", str, nbr_splits);
	while (str[++i] && j <= nbr_splits)
	{
		if (str[i] == SPACE || str[i] == TAB)
		{
			if (var > 0)
			{
				printf("%d + %d - (%zu - %zu) + (%zu - %zu)\n", \
				i, exp->spot_of_var[var], exp->current_o_len,  exp->o_var_len[var], exp->tot_t_len, exp->t_var_len[var]);
				exp->spot_to_split_var[var][j] = i + exp->spot_of_var[var] - \
				(exp->current_o_len - exp->o_var_len[var]) + \
				(exp->tot_t_len - exp->t_var_len[var]);
			}
			else
				exp->spot_to_split_var[var][j] = i + exp->spot_of_var[var];
			printf("exp->spot_to_split_var[%d][%d]= %d\n", var, j, exp->spot_to_split_var[var][j]);
			j++;
		}
	}
	exp->spot_to_split_var[var][nbr_splits] = '\0';
	exp->nbr_splits += nbr_splits;
}

static int	translated_var_length(t_exp_var *exp, t_token *tk, char **environ)
{
	int		i;

	(void)tk;
	errno = VAR_NOT_FOUND;
	exp->var_trans = malloc(sizeof(char *) * (exp->nbr_var + 1));
	exp->t_var_len = malloc(sizeof(size_t) * (exp->nbr_var + 1));
	exp->spot_to_split_var = malloc(sizeof(int *) * (exp->nbr_var + 1));
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
			if (tk->var_not_quoted && (ft_strchr(exp->var_trans[i], SPACE) || \
			ft_strchr(exp->var_trans[i], TAB)))
				tk->flag_split = 1;
		}
		exp->t_var_len[i] = ft_strlen(exp->var_trans[i]);
		exp->tot_t_len += exp->t_var_len[i];
		exp->current_o_len += exp->o_var_len[i];
		if (exp->var_trans[i] == NULL)
			exp->nbr_splits += 0;
		else
			where_to_split(exp, exp->var_trans[i], i);
		i++;
	}
	exp->spot_to_split_var[exp->nbr_var] = 0;
	return (1);
}

static void	replace_substr(t_var_replace *v, t_exp_var *exp, int i, int j)
{
	while (i < v->dst_size && j < (int)ft_strlen(v->str))
	{
		if (v->str[j] == D_QUOTE)
		{
			v->dest[i++] = v->str[j++];
			while (j < (int)ft_strlen(v->str) && v->str[j] != D_QUOTE)
			{
				if (v->str[j] == VAR)
				{
					v->var_size = 0;
					j++;
					while (i < v->dst_size && v->var_size < exp->t_var_len[v->var_nb])
						v->dest[i++] = exp->var_trans[v->var_nb][v->var_size++];
					if (v->var_nb < exp->nbr_var)
						j += exp->o_var_len[v->var_nb++] - 1;
				}
				else
					v->dest[i++] = v->str[j++];
			}
			v->dest[i++] = v->str[j++];
		}
		if (v->str[j] == S_QUOTE)
		{
			v->dest[i++] = v->str[j++];
			while ((v->str[j] != '\0' && v->str[j] != S_QUOTE))
				v->dest[i++] = v->str[j++];
			v->dest[i++] = v->str[j++];
		}
		else if (v->str[j] == VAR)
		{
			v->var_size = 0;
			j++;
			while (i < v->dst_size && v->var_size < exp->t_var_len[v->var_nb])
				v->dest[i++] = exp->var_trans[v->var_nb][v->var_size++];
			if (v->var_nb < exp->nbr_var)
				j += exp->o_var_len[v->var_nb++] - 1;
		}
		else
			v->dest[i++] = v->str[j++];
	}
	while (i <= v->dst_size)
		v->dest[i++] = '\0';
}

static char	*replace_substr_init(t_exp_var *exp, char *str, int dst_size)
{
	t_var_replace	v;
	int				i;
	int				j;

	i = 0;
	j = 0;
	v.var_nb = 0;
	if (dst_size <= 0)
		return (NULL);
	v.dest = malloc(sizeof(char) * (dst_size + 1));
	if (!v.dest)
		return (NULL);
	ft_memset(v.dest, 0, sizeof(v.dest));
	v.dst_size = dst_size;
	v.str = str;
	replace_substr(&v, exp, i, j);
	return (v.dest);
}

int	search_variables(t_data *d, int i, char **environ)
{
	char		*s;
	int			fct_expt;
	t_token		*tk;
	t_exp_var	exp;

	tk = &d->pars.tks[i];
	ft_memset(&exp, 0, sizeof(exp));
	fct_expt = 0;
	if (i > 0 && d->pars.tks[i - 1].type == BUILTIN && \
	ft_str_in_str("export", d->pars.tks[i - 1].ptr))
		fct_expt = 1;
	s = ft_strdup(tk->ptr);
	exp.nbr_var = count_variables(tk, s, fct_expt);
	if (exp.nbr_var == 0)
		tk->modif_word = ft_strdup(tk->ptr);
	else
	{
		original_var_length(s, &exp);
		translated_var_length(&exp, tk, environ);
		exp.t_token_len = ft_strlen(s) - exp.tot_o_len + exp.tot_t_len;
		exp.tmp_modif_word = replace_substr_init(&exp, s, exp.t_token_len);
		printf("exp->tmp_modif_word : %s\n", exp.tmp_modif_word);
		if (!word_splitting(d, tk, &exp, fct_expt))
			return (0);
		free_expand_struct(&exp);
	}
	ft_free_str(&s);
	return (1);
}
