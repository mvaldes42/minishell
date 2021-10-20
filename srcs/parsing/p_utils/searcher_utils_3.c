/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:57:10 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/20 12:25:00 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static int	count_variables_var(t_token *tk, char *str, int i, int export_case)
{
	if (str[i] == VAR)
	{
		if (!export_case)
			tk->var_not_quoted = 1;
		return (1);
	}
	return (0);
}

int	count_variables(t_token *tk, char *str, int fct_expt)
{
	size_t		i;
	int			var_nbr;
	bool		export_case;

	i = -1;
	var_nbr = 0;
	export_case = 0;
	while (++i < ft_strlen(str))
	{
		if (str[i] == S_QUOTE)
		{
			while (++i < ft_strlen(str) && str[i] != S_QUOTE)
				;
		}
		else if (str[i] == D_QUOTE)
		{
			while (++i < ft_strlen(str) && str[i] != D_QUOTE)
				if (str[i] == VAR)
					var_nbr++;
		}
		else if (str[i] == '=' && fct_expt)
			export_case = 1;
		var_nbr += count_variables_var(tk, str, i, export_case);
	}
	return (var_nbr);
}

int	translated_var_length(t_exp_var *exp, t_token *tk, char **environ)
{
	int		i;

	(void)tk;
	errno = VAR_NOT_FOUND;
	exp->current_o_len = 0;
	i = 0;
	while (i < exp->nbr_var)
	{
		exp->var_trans[i] = ft_getenv(++exp->var_name[i], environ);
		--exp->var_name[i];
		exp->t_var_len[i] = ft_strlen(exp->var_trans[i]);
		if (exp->o_var_len[i] == 1 && exp->t_var_len[i] == 0)
			exp->t_var_len[i] = 1;
		exp->tot_t_len += exp->t_var_len[i];
		exp->current_o_len += exp->o_var_len[i];
		i++;
	}
	return (1);
}
