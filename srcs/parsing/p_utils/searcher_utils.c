/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:42:09 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/02 10:21:04 by mvaldes          ###   ########.fr       */
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
			srch->o_var_len[j] = 1;
			while (str[++i] && str[i] != VAR && str[i] != SPACE && \
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

static int	translated_var_length(t_searcher *srch, char **environ)
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
		srch->t_var_len[i] = ft_strlen(srch->var_trans[i]);
		srch->tot_t_len += srch->t_var_len[i];
		i++;
	}
	return (1);
}

static char	*replace_substr(t_searcher *srch, char *str, int dst_size, int type)
{
	t_var_replace	v;
	int				i;
	int				j;

	i = 0;
	if (type == WORD_VAR)
		j = 0;
	else
		j = 1;
	v.var_nb = 0;
	if (dst_size <= 0)
		return (NULL);
	v.dest = malloc(sizeof(char *) * (dst_size));
	while (i < dst_size && str[j] != '\0')
	{
		if (str[j] == VAR)
		{
			v.var_size = 0;
			j++;
			while (v.var_size < srch->t_var_len[v.var_nb])
				v.dest[i++] = srch->var_trans[v.var_nb][v.var_size++];
			j += srch->o_var_len[v.var_nb++] - 1;
		}
		else
			v.dest[i++] = str[j++];
	}
	v.dest[i] = '\0';
	return (v.dest);
}

int	weak_word_search(t_token *token, t_searcher *srch, char **environ)
{
	char	*s;

	s = ft_strdup(token->ptr);
	srch->nbr_var = count_variables(s);
	original_var_length(s, srch);
	translated_var_length(srch, environ);
	if (token->type == WORD && srch->nbr_var == 0)
		return (1);
	else if (token->type == WORD && srch->nbr_var > 0)
	{
		srch->t_token_len = ft_strlen(s) - srch->tot_o_len + srch->tot_t_len;
		token->type = WORD_VAR;
	}
	else
		srch->t_token_len = ft_strlen(s) - 2 \
		- srch->tot_o_len + srch->tot_t_len;
	token->trans_weak = replace_substr(srch, s, srch->t_token_len, token->type);
	if (!token->trans_weak)
		return (0);
	ft_free_str(&s);
	free_srch_struct(srch);
	return (1);
}
