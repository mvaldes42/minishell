/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:11:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/24 16:58:32 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/libft/libft.h"
# include <stddef.h>
# include <stdio.h>
# include <string.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

const char	*g_build_in[] =
{"echo", "cd", "pwd", "export", "unset", "env", "exit"};

typedef enum e_token_type_lst
{
	CHAR_SINGLE_QUOTE = '\'',
	CHAR_DOUBLE_QUOTE = '\"',
	CHAR_GREATER = '>',
	CHAR_LESSER = '<',
	CHAR_PIPE = '|',
	CHAR_WHITESPACE = ' ',
	CHAR_TAB = '\t',
	CHAR_NEWLINE = '\n',
	CHAR_NULL = 0,
	CHAR_EXPANSION = '$',
	CHAR_SINGLE_WILD = '?',
}	t_token_type;

typedef struct s_token_id
{
	int		token_type;
	char			*token_ptr;
}	t_token_id;

typedef struct s_lexer
{
	t_token_id	*tokens_lst;
	long		token_nbr;
}	t_lexer;

typedef struct s_data
{
	t_lexer	*s_tokens;
}	t_data;

#endif
