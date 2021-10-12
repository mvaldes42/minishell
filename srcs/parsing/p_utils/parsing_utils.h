/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 14:03:22 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 13:54:37 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_UTILS_H
# define PARSING_UTILS_H

# include <stddef.h>
# include <sys/stat.h>
# include <stdbool.h>

# define S_QUOTE '\''
# define D_QUOTE '\"'
# define R_OUT '>'
# define R_IN '<'
# define PIPE_C '|'
# define VAR '$'
# define SPACE ' '
# define TAB '\t'

# define OPT_ECHO "-n"

typedef enum e_tk_types
{
	UNDEF = 0,
	WORD = 1,
	PIPE = 2,
	REDIR_OUT = 3,
	REDIR_IN = 4,
	READ_IN = 5,
	REDIR_OUT_A = 6,
	EXIT_STS = 7,
	FUNCTION = 8,
	BUILTIN = 9
}	t_tk_types;

typedef struct s_token
{
	int		type;
	char	*ptr;
	bool	redir;
	bool	echo_opt;
	bool	var_not_quoted;
	char	*modif_word;
	char	*tk_fct_path;
}	t_token;

typedef struct s_exp_var
{
	int		nbr_var;
	size_t	*o_var_len;
	size_t	*t_var_len;
	size_t	tot_o_len;
	size_t	current_o_len;
	size_t	tot_t_len;
	char	*tmp_modif_word;
	char	**var_name;
	char	**var_trans;
	size_t	t_token_len;
}	t_exp_var;

typedef struct s_parsing
{
	t_token	*tks;
	char	**unspec_tk;
	int		tk_nbr;
	int		cmd_nbr;
	int		*argv_size;
}	t_parsing;

typedef struct s_split
{
	char		**dest;
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
	int		dst_size;
	char	*str;
}	t_var_replace;

typedef struct s_funct_ext
{
	struct stat	statbuf;
	char		*dest_dir;
	char		*d_ptr;
	char		*func_name;
}	t_funct_ext;

typedef struct s_data		t_data;
typedef struct s_parsing	t_parsing;
typedef struct s_commands	t_commands;

// TOKEN_COUNT.C
int		token_count(const char *s);
// TOKEN_COUNT_2.C
int		redir_case_general(char **dup, int count, char r_type, char other_r);
// TOKEN_SPLIT.C
char	**token_split(char const *str, int token_nbr);
// SEARCHER.C
void	search_path_str(t_data *d, char ***env_path);
int		remove_quotes(char **expanded_word);
int		expand_word(t_data *d, char **env_path, int i);
// SEARCHER_UTILS.C
int		search_variables(t_data *d, int i, char **env);
// SEARCHER_UTILS_3.C
int		count_variables(t_token *tk, char *str, int fct_expt);
// WORD_SPLITTING.C
int		word_splitting(t_data *d, t_token *tk, t_exp_var *exp, int fct_expt);
// SEARCHER_UTILS_2.C
int		search_funct_ext(t_parsing *parsing, t_token *token, char **env_path);
void	free_expand_struct(t_exp_var *expand);
int		free_env_path(t_data *data, char ***env_path);
//CMD_TABlE_.C
int		input_command_table(t_data *d);
// CMD_TABLE_UTILS.C
int		cmd_redir_case(t_data *d, t_token *tks, t_commands *cmd, int i);
int		cmd_args(t_data *d, t_commands *cmd, t_token *tks, int i);
int		input_cmd_fct_builtin(t_commands *cmd);
// PRINT_TABS.C
void	print_lexer_tab(t_parsing	*lx);
void	print_parsing_tab(t_data *data);
void	print_cmd_tab(t_data *d);

#endif
