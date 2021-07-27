/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 16:09:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/27 14:13:32 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"

static int	word_case_count(char **dup, char c, int count)
{
	while (**dup && **dup != c && **dup != '\'' && **dup != '\"' && \
	**dup != '|' && **dup != '<' && **dup != '>' && **dup != '$')
		*dup += 1;
	count++;
	return (count);
}

static int	quotes_case_count(char **dup, int count)
{
	if (**dup && **dup == '\'')
	{
		*dup += 1;
		while (**dup && **dup != '\'')
			*dup += 1;
		count++;
		*dup += 1;
	}
	else if (**dup && **dup == '\"')
	{
		*dup += 1;
		while (**dup && **dup != '\"')
			*dup += 1;
		count++;
		*dup += 1;
	}
	return (count);
}

static int	spe_case_count(char **dup, char c, int count)
{
	if (**dup == '|')
	{
		count++;
		*dup += 1;
	}
	else if (**dup == '$')
	{
		*dup += 1;
		if (**dup == '?')
			*dup += 1;
		else
		{
			while (**dup && **dup != c && **dup != '\'' && **dup != '\"' && \
			**dup != '|' && **dup != '<' && **dup != '>' && **dup != '$' && \
			**dup != '?')
				*dup += 1;
		}
		count += 1;
	}
	return (count);
}
// count = 0 have to be replaced with an erro message

static int	redir_case_count(char **dup, int count)
{
	if (**dup == '<')
	{
		*dup += 1;
		if (**dup == '>')
			count = 0;
		else if (**dup == '<')
			*dup += 1;
		if (**dup == '<' || **dup == '>')
			count = 0;
		else
			count += 1;
	}
	else if (**dup == '>')
	{
		*dup += 1;
		if (**dup == '<')
			count = 0;
		else if (**dup == '>')
			*dup += 1;
		if (**dup == '<' || **dup == '>')
			count = 0;
		else
			count += 1;
	}
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
		if (*dup && *dup != c && *dup != '\'' && *dup != '\"' && *dup != '|'\
		&& *dup != '<' && *dup != '>' && *dup != '$')
			count = word_case_count(&dup, c, count);
		if (*dup && (*dup == '\'' || *dup == '\"'))
			count = quotes_case_count(&dup, count);
		else if (*dup && (*dup == '|' || *dup == '$'))
			count = spe_case_count(&dup, c, count);
		else if (*dup && (*dup == '<' || *dup == '>'))
		{
			count = redir_case_count(&dup, count);
			if (count == 0)
				break ;
		}
	}
	free(ptr);
	return (count);
}
