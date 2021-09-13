/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 14:42:09 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/13 16:42:26 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static int	count_variables(t_token *tk, char *str)
{
	int	i;
	int	var_nbr;

	(void)tk;
	i = -1;
	var_nbr = 0;
	while (str[++i])
	{
		if (str[i] == S_QUOTE)
			while (str[++i] && str[i] != S_QUOTE)
				;
		else if (str[i] == D_QUOTE)
		{
			while (str[++i] && str[i] != D_QUOTE)
				if (str[i] == VAR)
					var_nbr++;
		}
		else if (str[i] == VAR)
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
		printf("srch->var_trans[%d]: %s\n", i, srch->var_trans[i]);
		printf("%s\n", srch->var_name[i]);
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
	j = 0;
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
	printf("v.dest: %s\n", v.dest);
	return (v.dest);
}

static int	count_word_split(t_searcher *srch)
{
	int		i;
	int		count;
	char	*tmp;	

	i = 0;
	count = 0;
	tmp = srch->tmp_modif_word;
	while (tmp[i])
	{
		if (tmp[i] == D_QUOTE)
			while (tmp[++i] && tmp[i] != D_QUOTE)
				;
		if (tmp[i] == SPACE || tmp[i] == TAB)
			count += 1;
		i++;
	}
	return (count);
}

static int	reattribute_tokens(t_data *d, int tk_to_add)
{
	t_token	*tmp_tokens;
	t_token	tk;
	int		i;

	i = 0;
	tmp_tokens = malloc(sizeof(t_token) * (d->pars.tk_nbr + tk_to_add + 1));
	if (!(tmp_tokens))
		return (0);
	while (i < d->pars.tk_nbr)
	{
		tk = d->pars.tks[i];
		tmp_tokens[i].type = tk.type;
		tmp_tokens[i].ptr = ft_strdup(tk.ptr);
		printf("tmp_tokens[%d].ptr: %s\n", i, tmp_tokens[i].ptr);
		ft_free_str(&tk.ptr);
		tmp_tokens[i].redir = tk.redir;
		tmp_tokens[i].echo_opt = tk.echo_opt;
		i++;
	}
	free(d->pars.tks);
	return (1);
}

static int	word_splitting(t_data *d, t_token *tk, t_searcher *srch)
{
	int		tk_to_add;

	(void)d;
	(void)tk;
	tk_to_add = count_word_split(srch);
	printf("tk_to_add : %d\n", tk_to_add);
	reattribute_tokens(d, tk_to_add);
	return (1);
}

int	search_variables(t_data *d, t_token *tk, t_searcher *srch, char **environ)
{
	char	*s;

	s = ft_strdup(tk->ptr);
	srch->nbr_var = count_variables(tk, s);
	if (srch->nbr_var == 0)
		tk->modif_word = ft_strdup(tk->ptr);
	else
	{
		original_var_length(s, srch);
		translated_var_length(srch, environ);
		srch->t_token_len = ft_strlen(s) - srch->tot_o_len + srch->tot_t_len;
		srch->tmp_modif_word = replace_substr(srch, s, srch->t_token_len);
		if (!word_splitting(d, tk, srch))
			return (0);
		free_srch_struct(srch);
	}
	ft_free_str(&s);
	if (!tk->modif_word)
		return (0);
	return (1);
}
