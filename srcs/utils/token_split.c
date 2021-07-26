/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 15:23:03 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/26 17:11:35 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general_utils.h"

static void	regular_word(t_split *s, const char *str)
{
	while (str[s->end] && str[s->end] != s->c && str[s->end] != '\'' && \
	str[s->end] != '\"' && str[s->end] != '|' && str[s->end] != '<' && \
	str[s->end] != '>' && str[s->end] != '$')
		s->end++;
	s->dest[s->i] = ft_substr(str, s->start, (s->end - s->start));
	s->start = s->end;
	s->i++;
}

static void	quote_word(t_split *s, const char *str)
{
	if (str[s->end] == '\'')
	{
		s->end += 1;
		while (str[s->end] && str[s->end] != '\'')
			s->end++;
		s->end += 1;
		s->dest[s->i] = ft_substr(str, s->start, (s->end - s->start));
		s->start = s->end;
		s->i++;
	}
	else if (str[s->end] == '\"')
	{
		s->end += 1;
		while (str[s->end] && str[s->end] != '\"')
			s->end++;
		s->end += 1;
		s->dest[s->i] = ft_substr(str, s->start, (s->end - s->start));
		s->start = s->end;
		s->i++;
	}
}

static void	spe_word(t_split *s, const char *str)
{
	if (str[s->end] == '|')
	{
		s->dest[s->i] = malloc(sizeof(char) * 2);
		s->dest[s->i][0] = str[s->end];
		s->dest[s->i][1] = '\0';
		s->end += 1;
		s->start = s->end;
		s->i++;
	}
	else if (str[s->end] == '$')
	{
		s->end += 1;
		if (str[s->end] == '?')
			s->end += 1;
		else
		{
			while (str[s->end] && str[s->end] != s->c && str[s->end] != '\'' && \
			str[s->end] != '\"' && str[s->end] != '|' && str[s->end] != '<' && \
			str[s->end] != '>' && str[s->end] != '$')
				s->end++;
		}
		s->dest[s->i] = ft_substr(str, s->start, (s->end - s->start));
		s->start = s->end;
		s->i++;
	}
}

static void	redir_word(t_split *s, const char *str)
{
	s->end += 1;
	if (str[s->end] == '>' || str[s->end] == '<')
		s->end += 1;
	s->dest[s->i] = ft_substr(str, s->start, (s->end - s->start));
	s->start = s->end;
	s->i++;
}

static void	special_split_2(t_split *s, const char *str)
{
	while (s->i != s->w_count)
	{
		while (str[s->start] && str[s->start] == s->c)
			s->start++;
		if (!str[s->start])
			break ;
		s->end = s->start;
		if (str[s->end] && str[s->end] != s->c && str[s->end] != '\'' && \
		str[s->end] != '\"' && str[s->end] != '|' && str[s->end] != '<' && \
		str[s->end] != '>' && str[s->end] != '$')
			regular_word(s, str);
		if (str[s->end] && (str[s->end] == '\'' || str[s->end] == '\"'))
			quote_word(s, str);
		else if (str[s->end] && (str[s->end] == '|' || str[s->end] == '$'))
			spe_word(s, str);
		else if (str[s->end] && (str[s->end] == '<' || str[s->end] == '>'))
			redir_word(s, str);
	}
}

char	**token_split(char const *str, char c)
{
	t_split		s_data;

	if (!(str))
		return (NULL);
	ft_memset(&s_data, 0, sizeof(t_split));
	s_data.c = c;
	s_data.w_count = token_count(str, c);
	s_data.dest = (char **)malloc(sizeof(char *) * (s_data.w_count + 1));
	if (!s_data.dest)
		return (NULL);
	special_split_2(&s_data, str);
	s_data.dest[s_data.w_count] = NULL;
	return (s_data.dest);
}
