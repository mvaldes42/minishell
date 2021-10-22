/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_count_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:37 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/21 18:01:55 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_utils.h"
#include "../../minishell.h"

int	redir_case_general(char **dup, int count, char r_type, char other_r)
{
	errno = UNEXPECTED_TK;
	*dup += 1;
	if (**dup == other_r)
		return (0);
	else if (**dup == r_type)
		*dup += 1;
	if (**dup == r_type || **dup == other_r)
		return (0);
	else
		count += 1;
	return (count);
}
