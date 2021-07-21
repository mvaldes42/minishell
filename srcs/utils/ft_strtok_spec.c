/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 14:52:47 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/02 17:45:00 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

// static int	quotes_case(char *s, char ***dest, int i)
// {
// 	int	start;

// 	start = i;
// 	if (s[i] == '\'')
// 	{
// 		i += 1 ;
// 		while (s[i] != '\'')
// 			i++;
// 		**dest = ft_substr(s, start, (i - start));
// 		*dest += 1;
// 		i += 1;
// 	}
// 	else if (s[i] == '\"')
// 	{
// 		i += 1 ;
// 		while (s[i] != '\"')
// 			i++;
// 		**dest = ft_substr(s, start, (i - start));
// 		*dest += 1;
// 		i += 1;
// 	}
// 	return (i);
// }

// static int	miscellaneous_case(int count, char **s, char *sep)
// {
// 	if (**s == '$')
// 	{
// 		count += 1;
// 		*s += 1;
// 		while (**s != '\0' && ft_strrchr(sep, **s) == NULL)
// 			*s += 1;
// 	}
// 	else if (**s == '|')
// 	{
// 		count += 1;
// 		*s += 1;
// 	}
// 	return (count);
// }

// static int	redirect_case(int count, char **s)
// {
// 	if (**s == '>')
// 	{
// 		*s += 1;
// 		count += 1;
// 		if (**s == '>')
// 			*s += 1;
// 	}
// 	else if (**s == '<')
// 	{
// 		*s += 1;
// 		count += 1;
// 		if (**s == '<')
// 			*s += 1;
// 	}
// 	return (count);
// }

static void	word_case(t_data *data, char *s, int i)
{
	int		start;

	if (s[i] == ' ')
	{
		while (s[i] == ' ')
			i += 1;
	}
	else
	{
		start = i;
		while (s[i] != '\0' && ft_strrchr(" \'\"|<>$", s[i]) == NULL)
			i += 1;
		data->s_tokens.unspec_tk[data->s_tokens.unspec_tk_nb] = ft_substr(s, start, (i - start));
		data->s_tokens.unspec_tk_nb += 1;
	}
}

char	**ft_strtok_spec(t_data *data, char *s, int tk_nbr)
{
	int		i;

	if (!(s))
		return (NULL);
	data->s_tokens.unspec_tk = (char **)malloc(sizeof(char *) * (tk_nbr + 1));
	// while (s[i] != '\0')
	// {
	// 	// if (s[i] == '\'' || s[i] == '\"')
	// 	// 	i = quotes_case(s, dest, i);
	// 	// else if (*s == '$' || *s == '|')
	// 	// 	i = miscellaneous_case(count, &s, sep, i);
	// 	// else if (*s == '>' || *s == '<')
	// 		// i = redirect_case(count, &s, i);
	// 	// else
	// 		word_case(data, s, i);
	// }
	// int	j;
	// while (j < data->s_tokens.unspec_tk_nb)
	// {
	// 	printf("%s\n", data->s_tokens.unspec_tk[j]);
	// 	j++;
	// }
	return (data->s_tokens.unspec_tk);
}
