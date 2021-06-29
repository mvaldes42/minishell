/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:11:08 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/29 17:34:00 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/libft/libft.h"
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

static const char	*g_build_in[] =
{"echo", "cd", "pwd", "export", "unset", "env", "exit"};

# define CHAR_SINGLE_QUOTE '\''
# define CHAR_DOUBLE_QUOTE '\"'
# define CHAR_RED_OUT '>'
# define STR_RED_OUT_APP '>' + '>'
# define CHAR_RED_IN '<'
# define STR_READ_IN '<' + '<'
# define CHAR_PIPE '|'
# define CHAR_NULL 0
# define CHAR_EXP '$'
# define STR_EXIT_STAT '$' + '?'
# define CHAR_WHITESPACE ' '
# define CHAR_ALPHA -1

# define OPT_ECHO "-n"

typedef struct s_token_id
{
	int		token_type;
	char	*token_ptr;
}	t_token_id;

typedef struct s_lexer
{
	t_token_id	*tk_lst;
	int			tk_nbr;
}	t_lexer;

typedef struct s_data
{
	t_lexer	s_tokens;
}	t_data;

char	*ft_strtok(char *s, const char *delim);

#endif