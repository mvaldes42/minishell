/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:09:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/27 12:09:40 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

static int	word_case_count(char **dup, char c, int count)
{
	while (**dup && **dup != c && **dup != S_QUOTE && **dup != D_QUOTE && **dup \
	!= PIPE_C && **dup != R_IN && **dup != R_OUT && **dup != VAR)
		*dup += 1;
	count++;
	return (count);
}

static int	quotes_case_general(char **dup, int count, char q_type)
{
	*dup += 1;
	while (**dup != q_type)
	{	
		if (**dup == '\0')
		{
			printf("error: missing quote\n");
			return (0);
		}
		*dup += 1;
	}
	if (**dup != '\0' && count != 0)
	{
		count++;
		*dup += 1;
	}
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

static int	spe_case_count(char **dup, char c, int count)
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
			while (**dup && **dup != c && **dup != S_QUOTE && **dup != D_QUOTE \
			&& **dup != PIPE_C && **dup != R_IN && **dup != R_OUT && **dup != \
			VAR && **dup != '?')
				*dup += 1;
		}
		count += 1;
	}
	return (count);
}

static int	redir_case_general(char **dup, int count, char r_type, char other_r)
{
	*dup += 1;
	if (**dup == other_r)
	{
		printf("error: near redirection symbol\n");
		return (0);
	}
	else if (**dup == r_type)
		*dup += 1;
	if (**dup == r_type || **dup == other_r)
	{
		printf("error: near redirection symbol\n");
		return (0);
	}
	else
		count += 1;
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

int	token_count(const char *s, char c)
{
	char			*dup;
	unsigned int	count;
	char			*ptr;

	count = 0;
	dup = ft_strdup(s);
	ptr = dup;
	while (*dup)
	{
		while (*dup && *dup == c)
			dup++;
		if (*dup && *dup != c && *dup != S_QUOTE && *dup != D_QUOTE && \
		*dup != PIPE_C && *dup != R_IN && *dup != R_OUT && *dup != VAR)
			count = word_case_count(&dup, c, count);
		if (*dup && (*dup == S_QUOTE || *dup == D_QUOTE))
		{
			count = quotes_case_count(&dup, count);
			if (count == 0)
				return (count);
		}
		else if (*dup && (*dup == PIPE_C || *dup == VAR))
			count = spe_case_count(&dup, c, count);
		else if (*dup && (*dup == R_IN || *dup == R_OUT))
		{
			count = redir_case_count(&dup, count);
			if (count == 0)
				return (count);
		}
	}
	free(ptr);
	return (count);
}
