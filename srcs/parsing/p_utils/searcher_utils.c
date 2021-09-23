/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:42:09 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/23 16:45:43 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static void	original_var_length(char *str, t_searcher *srch)
{
	int		j;
	int		i;
	int		start;

	i = 0;
	j = 0;
	srch->o_var_len = malloc(sizeof(size_t) * (srch->nbr_var + 1));
	srch->var_name = malloc(sizeof(char **) * (srch->nbr_var + 1));
	while (str[i] != '\0' && j < srch->nbr_var)
	{
		if (str[i] == VAR)
		{
			start = i;
			srch->o_var_len[j] = 1;
			while (str[++i] && str[i] != VAR && str[i] != SPACE && \
			str[i] != TAB && str[i] != S_QUOTE && str[i] != D_QUOTE)
				srch->o_var_len[j] += 1;
			srch->tot_o_len += srch->o_var_len[j];
			srch->var_name[j] = ft_substr(str, start, i - start);
			j += 1;
		}
		else
			i++;
	}
}

static int	translated_var_length(t_searcher *srch, t_token *tk, char **environ)
{
	int		i;

	errno = VAR_NOT_FOUND;
	srch->var_trans = malloc(sizeof(char **) * (srch->nbr_var + 1));
	srch->t_var_len = malloc(sizeof(size_t *) * (srch->nbr_var + 1));
	i = 0;
	while (i < srch->nbr_var)
	{
		if (ft_strncmp(srch->var_name[i], "$?", 2) == 0)
			srch->var_trans[i] = ft_strdup("exit_status(do do later)");
		else
		{
			srch->var_trans[i] = ft_getenv(++srch->var_name[i], environ);
			--srch->var_name[i];
		}
		if (tk->var_not_quoted && (ft_strchr(srch->var_trans[i], SPACE) || \
		ft_strchr(srch->var_trans[i], TAB)))
			tk->flag_split = 1;
		srch->t_var_len[i] = ft_strlen(srch->var_trans[i]);
		srch->tot_t_len += srch->t_var_len[i];
		i++;
	}
	return (1);
}

// printf("(translated_var_length) > srch->var_trans[%d]: %s\n",
// i, srch->var_trans[i]);
// printf("srch->var_name[%d]: %s\n", i, srch->var_name[i]);

static char	*replace_substr(t_searcher *srch, char *str, int dst_size)
{
	t_var_replace	v;
	int				i;
	int				j;

	i = 0;
	j = 0;
	v.var_nb = 0;
	if (dst_size <= 0)
		return (NULL);
	v.dest = malloc(sizeof(char *) * (dst_size));
	ft_memset(v.dest, 0, sizeof(v.dest));
	printf("dst_size: %d\n", dst_size);
	while (i < dst_size && str[j] != '\0')
	{
		// printf("srch->var_trans[%d]: %s, dst_size: %d\n", v.var_nb, srch->var_trans[v.var_nb], dst_size);
		// printf("srch->t_var_len[%d] : %zu\n", v.var_nb, srch->t_var_len[v.var_nb]);
		if (str[j] == S_QUOTE)
		{
			j += 1;
			while ((str[j] != '\0' && str[j] != S_QUOTE))
				v.dest[i++] = str[j++];
			j += 1;
			printf("str[%d] : %c\n", j, str[j]);
		}
		else if (str[j] == VAR)
		{
			v.var_size = 0;
			j++;
			while (i < dst_size && v.var_size < srch->t_var_len[v.var_nb])
			{
				printf("srch->nbr_v: %d\n", srch->nbr_var);
				printf("v.var_size: %zu < srch->t_var_len[%d] : %zu, srch->var_trans[v.var_nb][v.var_size] : %c\n", v.var_size, v.var_nb, srch->t_var_len[v.var_nb], srch->var_trans[v.var_nb][v.var_size]);
				printf("i :%d < dst_size: %d\n", i, dst_size);
				v.dest[i] = srch->var_trans[v.var_nb][v.var_size];
				i++;
				v.var_size++;

			}
			if (v.var_nb < srch->nbr_var)
				j += srch->o_var_len[v.var_nb++] - 1;
		}
		else
			v.dest[i++] = str[j++];
	}
	v.dest[i] = '\0';
	return (v.dest);
}

int	search_variables(t_data *d, int i, t_searcher *srch, char **environ)
{
	char	*s;
	int		fct_expt;
	t_token	*tk;

	tk = &d->pars.tks[i];
	fct_expt = 0;
	if (i > 0 && d->pars.tks[i - 1].type == BUILTIN && \
	ft_str_in_str("export", d->pars.tks[i - 1].ptr))
		fct_expt = 1;
	s = ft_strdup(tk->ptr);
	srch->nbr_var = count_variables(tk, s, fct_expt);
	if (srch->nbr_var == 0)
		tk->modif_word = ft_strdup(tk->ptr);
	else
	{
		original_var_length(s, srch);
		translated_var_length(srch, tk, environ);
		srch->t_token_len = ft_strlen(s) - srch->tot_o_len + srch->tot_t_len;
		srch->tmp_modif_word = replace_substr(srch, s, srch->t_token_len);
		if (!word_splitting(d, tk, srch, fct_expt))
			return (0);
		free_srch_struct(srch);
	}
	ft_free_str(&s);
	return (1);
}
