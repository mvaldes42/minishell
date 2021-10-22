/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:09:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/21 18:02:07 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

static int	quotes_case_general(char **dup, char q_type)
{
	errno = MISSING_QUOTE;
	*dup += 1;
	while (**dup != '\0' && **dup != q_type)
		*dup += 1;
	if (**dup == '\0')
		return (0);
	return (1);
}

static int	word_case_count(char **dup, int count)
{
	errno = MISSING_QUOTE;
	while (**dup != '\0')
	{
		if ((**dup == SPACE || **dup == TAB || **dup == PIPE_C || \
		**dup == R_IN || **dup == R_OUT))
			break ;
		else if (**dup == S_QUOTE)
		{
			if (!quotes_case_general(dup, S_QUOTE))
				return (0);
		}
		else if (**dup == D_QUOTE)
		{
			if (!quotes_case_general(dup, D_QUOTE))
				return (0);
		}
		*dup += 1;
	}
	count++;
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
			while (**dup && **dup != SPACE && **dup != TAB && **dup != PIPE_C \
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
