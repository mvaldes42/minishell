/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:37 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/27 15:48:10 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"

int	redir_case_general(char **dup, int count, char r_type, char other_r)
{
	char	*error_str;

	error_str = "error: wrong redirection symbol\n";
	*dup += 1;
	if (**dup == other_r)
	{
		printf("%s", error_str);
		return (0);
	}
	else if (**dup == r_type)
		*dup += 1;
	if (**dup == r_type || **dup == other_r)
	{
		printf("%s", error_str);
		return (0);
	}
	else
		count += 1;
	return (count);
}

int	quotes_case_general(char **dup, int count, char q_type)
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
