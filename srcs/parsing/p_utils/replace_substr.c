/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_substr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:44:37 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 14:44:59 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static void	double_quotes_sub(t_var_replace *v, t_exp_var *exp, int *i, int *j)
{
	v->dest[(*i)++] = v->str[(*j)++];
	while (*j < (int)ft_strlen(v->str) && v->str[*j] != D_QUOTE)
	{
		if (v->str[*j] == VAR)
		{
			v->var_size = 0;
			(*j)++;
			while (*i < v->dst_size && \
			v->var_size < exp->t_var_len[v->var_nb])
				v->dest[(*i)++] = exp->var_trans[v->var_nb][v->var_size++];
			if (v->var_nb < exp->nbr_var)
				*j += exp->o_var_len[v->var_nb++] - 1;
		}
		else
			v->dest[(*i)++] = v->str[(*j)++];
	}
	v->dest[(*i)++] = v->str[(*j)++];
}

static void	replace_substr(t_var_replace *v, t_exp_var *exp, int i, int j)
{
	while (i < v->dst_size && j < (int)ft_strlen(v->str))
	{
		if (v->str[j] == D_QUOTE)
			double_quotes_sub(v, exp, &i, &j);
		if (j < (int)ft_strlen(v->str) && v->str[j] == S_QUOTE)
		{
			v->dest[i++] = v->str[j++];
			while ((v->str[j] != '\0' && v->str[j] != S_QUOTE))
				v->dest[i++] = v->str[j++];
			v->dest[i++] = v->str[j++];
		}
		else if (j < (int)ft_strlen(v->str) && v->str[j] == VAR)
		{
			v->var_size = 0;
			j++;
			while (i < v->dst_size && v->var_size < exp->t_var_len[v->var_nb])
				v->dest[i++] = exp->var_trans[v->var_nb][v->var_size++];
			if (v->var_nb < exp->nbr_var)
				j += exp->o_var_len[v->var_nb++] - 1;
		}
		else if (j < (int)ft_strlen(v->str))
			v->dest[i++] = v->str[j++];
	}
	while (i <= v->dst_size)
		v->dest[i++] = '\0';
}

char	*rplc_substr_init(t_exp_var *exp, char *str, int dst_size)
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
