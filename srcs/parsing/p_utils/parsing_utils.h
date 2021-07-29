/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:03:22 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/29 18:32:38 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include <stddef.h>
# include <sys/stat.h>

# define S_QUOTE '\''
# define D_QUOTE '\"'
# define R_OUT '>'
# define R_IN '<'
# define PIPE_C '|'
# define VAR '$'
# define SPACE ' '

# define OPT_ECHO "-n"

typedef enum e_tk_types
{
	UNDEF = 0,
	WORD = 1,
	PIPE = 2,
	VARIABLE = 3,
	REDIR_OUT = 4,
	REDIR_IN = 5,
	READ_IN = 6,
	REDIR_OUT_A = 7,
	EXIT_STS = 8,
	WEAK_WORD = 9,
	STRONG_WORD = 10
}	t_tk_types;

typedef struct s_token_id
{
	int		token_type;
	char	*token_ptr;
	char	*translated_tk;
	char	*translated_var;
	char	*fct_path;
}	t_token_id;

typedef struct s_searcher
{
	int		nbr_var;
	size_t	*o_var_len;
	size_t	*t_var_len;
	size_t	tot_o_len;
	size_t	tot_t_len;
	char	**var_name;
	char	**var_translated;
	size_t	t_token_len;
	char	**path_str;
}	t_searcher;

typedef struct s_parsing
{
	t_token_id	*tk_lst;
	char		**unspec_tk;
	int			tk_nbr;
	t_tk_types	token_types;
	int			commands_nbr;
}	t_parsing;

typedef struct s_split
{
	char		**dest;
	char		c;
	int			start;
	int			end;
	int			i;
	int			w_count;
}	t_split;

typedef struct s_var_replace
{
	char	*dest;
	size_t	var_size;
	int		var_nb;
}	t_var_replace;

int		token_count(const char *s, char c);
void	special_split_2(t_split *s, const char *str);
char	**token_split(char const *str, char c);

int		quotes_case_general(char **dup, int count, char q_type);
int		redir_case_general(char **dup, int count, char r_type, char other_r);
void	print_lexer_tab(t_parsing	*lx);

int		count_variables(char *str);
void	free_srch_struct(t_searcher *srch);
void	original_var_length(char *str, t_searcher *srch);
int		translated_var_length(t_searcher *srch);
char	*replace_substr(t_searcher *srch, char *str, int dst_size);

#endif
