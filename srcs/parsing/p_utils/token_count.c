/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:09:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/02 16:49:13 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static int	word_case_count(char **dup, int count)
{
	while (**dup && **dup != SPACE && **dup != TAB && **dup != PIPE_C \
	&& **dup != R_IN && **dup != R_OUT)
		*dup += 1;
	count++;
	return (count);
}

static int	quotes_case_count(char **dup, int count)
{
	if (**dup && **dup == S_QUOTE)
		count = quotes_case_general(dup, count, S_QUOTE);
	else if (**dup && **dup == D_QUOTE)
		count = quotes_case_general(dup, count, D_QUOTE);
	return (count);
}

static int	spe_case_count(char **dup, int count)
{
	if (**dup == PIPE_C)
	{
		count++;
		*dup += 1;
	}
	else if (**dup == VAR)
	{
		*dup += 1;
		if (**dup == '?')
			*dup += 1;
		else
		{
			while (**dup && **dup != SPACE &&  **dup != TAB && **dup != PIPE_C \
			&& **dup != R_IN && **dup != R_OUT && **dup != VAR && **dup != '?')
				*dup += 1;
		}
		count += 1;
	}
	return (count);
}

static int	redir_case_count(char **dup, int count)
{
	if (**dup == R_IN)
		count = redir_case_general(dup, count, R_IN, R_OUT);
	else if (**dup == R_OUT)
		count = redir_case_general(dup, count, R_OUT, R_IN);
	return (count);
}

int	token_count(const char *s)
{
	char			*str;
	unsigned int	count;
	char			*ptr;

	count = 0;
	str = ft_strdup(s);
	ptr = str;
	while (*str)
	{
		while (*str && (*str == SPACE || *str == TAB))
			str++;
		if (*str && *str != SPACE && *str != TAB && *str != PIPE_C && \
		*str != R_IN && *str != R_OUT)
			count = word_case_count(&str, count);
		else if (*str && (*str == S_QUOTE || *str == D_QUOTE))
			count = quotes_case_count(&str, count);
		else if (*str && (*str == PIPE_C || *str == VAR))
			count = spe_case_count(&str, count);
		else if (*str && (*str == R_IN || *str == R_OUT))
			count = redir_case_count(&str, count);
		if (count == 0)
			break ;
	}
	ft_free_str(&ptr);
	return (count);
}
