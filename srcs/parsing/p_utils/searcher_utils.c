/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:42:09 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/30 15:36:54 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static int	count_variables(char *str)
{
	int	i;
	int	var_nbr;

	i = -1;
	var_nbr = 0;
	while (str[++i])
	{
		if (str[i] == VAR)
			var_nbr++;
	}
	return (var_nbr);
}

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
			srch->o_var_len[j] = 0;
			while (str[i++] && str[i] != VAR && str[i] != SPACE && \
			str[i] != S_QUOTE && str[i] != D_QUOTE)
				srch->o_var_len[j] += 1;
			srch->tot_o_len += srch->o_var_len[j];
			srch->var_name[j] = ft_substr(str, start, i - start);
			j += 1;
		}
		else
			i++;
	}
}

static int	translated_var_length(t_searcher *srch)
{
	int		i;

	srch->var_trans = malloc(sizeof(char **) * (srch->nbr_var + 1));
	srch->t_var_len = malloc(sizeof(size_t *) * (srch->nbr_var + 1));
	i = 0;
	while (i < srch->nbr_var)
	{
		if (ft_strncmp(srch->var_name[i], "$?", 2) == 0)
			srch->var_trans[i] = ft_strdup("exit_status(do do later)");
		else
		{
			srch->var_trans[i] = getenv(++srch->var_name[i]);
			--srch->var_name[i];
		}
		if (srch->var_trans[i] == NULL)
		{
			printf("\n");
			return (0);
		}
		srch->t_var_len[i] = ft_strlen(srch->var_trans[i]);
		srch->tot_t_len += srch->t_var_len[i];
		i++;
	}
	return (1);
}

static char	*replace_substr(t_searcher *srch, char *str, int dst_size)
{
	t_var_replace	v;
	int				i;
	int				j;

	i = 0;
	j = 1;
	v.var_nb = 0;
	v.dest = malloc(sizeof(char *) * (dst_size));
	while (i < dst_size - 1 && str[j] != '\0')
	{
		if (str[j] == VAR)
		{
			v.var_size = 0;
			j++;
			while (v.var_size < srch->t_var_len[v.var_nb])
				v.dest[i++] = srch->var_trans[v.var_nb][v.var_size++];
			j += srch->o_var_len[v.var_nb++];
		}
		else
			v.dest[i++] = str[j++];
	}
	v.dest[i] = '\0';
	return (v.dest);
}

int	weak_word_search(t_token_id *token, t_searcher *srch)
{
	char	*o_s;

	o_s = ft_strdup(token->token_ptr);
	srch->nbr_var = count_variables(o_s);
	original_var_length(o_s, srch);
	if (!translated_var_length(srch))
		return (0);
	srch->t_token_len = ft_strlen(o_s) - \
	(srch->tot_o_len + 1) + srch->tot_t_len - 2;
	token->trans_weak = replace_substr(srch, o_s, srch->t_token_len);
	free(o_s);
	free_srch_struct(srch);
	return (1);
}
