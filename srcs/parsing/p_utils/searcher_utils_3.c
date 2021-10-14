/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 14:57:10 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/14 16:55:23 by mvaldes          ###   ########.fr       */
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
		// printf("-------------)str[%zu] : %c\n", i, str[i]);
		if (str[i] == S_QUOTE)
		{
			while (++i < ft_strlen(str) && str[i] != S_QUOTE)
				;
			// printf("single quote fin)str[%zu] : %c\n", i, str[i]);
		}
		else if (str[i] == D_QUOTE)
		{
			while (++i < ft_strlen(str) && str[i] != D_QUOTE)
				if (str[i] == VAR)
				{
					var_nbr++;
					// printf("var nbr = %d\n", var_nbr);
				}
			// printf("double quote fin)str[%zu] : %c\n", i, str[i]);
		}
		else if (str[i] == '=' && fct_expt)
			export_case = 1;
		var_nbr += count_variables_var(tk, str, i, export_case);
	}
	printf("var_nbr: %d\n", var_nbr);
	return (var_nbr);
}
