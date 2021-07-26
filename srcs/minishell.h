#ifndef MINISHELL_H
# define MINISHELL_H
# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <string.h>
# include <stddef.h>
# include <stdbool.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

# define CHAR_SINGLE_QUOTE '\''
# define CHAR_DOUBLE_QUOTE '\"'
# define CHAR_RED_OUT '>'
# define CHAR_RED_IN '<'
# define CHAR_PIPE '|'
# define CHAR_EXP '$'
# define CHAR_WHITESPACE ' '

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
}	t_searcher;

typedef struct s_parsing
{
	t_token_id	*tk_lst;
	char		**unspec_tk;
	int			tk_nbr;
	t_tk_types	token_types;
}	t_parsing;

typedef struct s_commands
{
	char	*name;
	char	*option;
	char	*arguments;
	int		fd_out;
	bool	redir_out;
}	t_commands;

// COMMAND EXAMPLE
// commands[0] = {
// name = "echo"
// option = "-n"
// arguments = "bonjour"
// fd_out = STDOUT
// redir_out = 0
// }

// commands[1] = {
// name = "echo"
// option = NULL
// arguments = "cool$HOME top/Usr/user42 super"
// fd_out = 3
// redir_out = 1
// }

typedef struct s_data
{
	char		*prompt;
	t_parsing	s_tokens;
	t_commands	*commands;

}	t_data;

static const char	*g_build_in[7] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit"};

int		parsing(t_data *data, char *line);
int		lexer(t_data *data, char *line);
int		searcher(t_data *data);

#endif
