/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:57:42 by mvaldes           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/08/30 17:38:44 by mvaldes          ###   ########.fr       */
=======
/*   Updated: 2021/08/31 15:20:24 by fcavillo         ###   ########.fr       */
>>>>>>> dancing queen 🕺🏾
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../lib/libft/libft.h"
# include "parsing/p_utils/parsing_utils.h"
# include "utils/general_utils.h"
# include "execute/execute.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stddef.h>
# include <string.h>
# include <stddef.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

typedef int	(*t_builtin)(char **args, char ***environ_var);

typedef struct s_functions
{
	char		*name;
	bool		builtin;
	t_builtin	builtin_ptr;
	char		*fct_path;

}	t_functions;

typedef struct s_redir_token
{
	int		type;
	char	*filename;
}	t_redir_token;

typedef struct s_commands
{
	int				id;
	t_functions		fct;
	char			**args;
	t_redir_token	*redirs;
}	t_commands;

typedef struct s_data
{
	char		*prompt;
	t_parsing	pars;
	t_commands	*cmds;
	char		**environ;
	bool		is_exit;
	pid_t 		*pid;
}	t_data;

int		parsing(t_data *data, char *line);
int		lexer(t_data *data, char *line);
int		searcher(t_data *data);
int		execute(t_data *data);

#endif

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