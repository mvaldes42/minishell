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
	char		**unspec_tk;
	int			unspec_tk_nb;
	int			tk_nbr;
}	t_lexer;

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
	t_lexer		s_tokens;
	t_commands	*commands;

}	t_data;

static const char	*g_build_in[7] = \
		{"echo", "cd", "pwd", "export", "unset", "env", "exit"};

int		lexer(t_data *data, char *line, t_lexer *lx);

#endif
