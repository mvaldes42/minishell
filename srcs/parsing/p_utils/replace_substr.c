/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_substr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:44:37 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/14 19:01:54 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static void	double_quotes_sub(t_var_replace *v, t_exp_var *exp, int *i, int *j)
{
	v->dest[(*i)++] = v->str[(*j)++];
	while (*j < (int)ft_strlen(v->str) && v->str[*j] != D_QUOTE \
			&& v->vnbr < exp->nbr_var)
	{
		if (v->str[*j] == VAR)
		{
			if (exp->o_var_len[v->vnbr] == 1 && exp->t_var_len[v->vnbr] == 1)
			{
				v->dest[(*i)++] = v->str[(*j)++];
				v->vnbr++;
			}
			else
			{
				(*j)++;
				v->vsize = 0;
				while (*i < v->dst_s && v->vsize < exp->t_var_len[v->vnbr])
					v->dest[(*i)++] = exp->var_trans[v->vnbr][v->vsize++];
				if (v->vnbr < exp->nbr_var)
					*j += exp->o_var_len[v->vnbr++] - 1;
			}
		}
		v->dest[(*i)] = v->str[(*j)];
		if (*j < (int)ft_strlen(v->str) && v->str[*j] == D_QUOTE)
			break ;
		(*i)++;
		(*j)++;
	}
	if (*j < (int)ft_strlen(v->str))
		v->dest[(*i)] = v->str[(*j)];
}

static void	replace_substr(t_var_replace *v, t_exp_var *exp, int i, int j)
{
	while (i < v->dst_s && j < (int)ft_strlen(v->str))
	{
		if (j < (int)ft_strlen(v->str) && v->str[j] == D_QUOTE)
			double_quotes_sub(v, exp, &i, &j);
		else if (j < (int)ft_strlen(v->str) && v->str[j] == S_QUOTE)
		{
			v->dest[i++] = v->str[j++];
			while ((v->str[j] != '\0' && v->str[j] != S_QUOTE))
				v->dest[i++] = v->str[j++];
			v->dest[i] = v->str[j];
		}
		if (j < (int)ft_strlen(v->str) && v->str[j] == VAR)
		{
			v->vsize = 0;
			j++;
			while (v->vnbr < exp->nbr_var && i < v->dst_s && v->vsize < exp->t_var_len[v->vnbr])
				v->dest[i++] = exp->var_trans[v->vnbr][v->vsize++];
			if (v->vnbr < exp->nbr_var)
				j += exp->o_var_len[v->vnbr++] - 1;
		}
		else if (j < (int)ft_strlen(v->str))
			v->dest[i++] = v->str[j++];
	}
	while (i <= v->dst_s)
		v->dest[i++] = '\0';
}

char	*rplc_substr_init(t_exp_var *exp, char *str, int dst_size)
{
	t_var_replace	v;
	int				i;
	int				j;

	i = 0;
	j = 0;
	v.vnbr = 0;
	if (dst_size <= 0)
		return (NULL);
	v.dest = malloc(sizeof(char) * (dst_size + 1));
	if (!v.dest)
		return (NULL);
	ft_memset(v.dest, 0, sizeof(v.dest));
	v.dst_s = dst_size;
	v.str = str;
	replace_substr(&v, exp, i, j);
	return (v.dest);
}
