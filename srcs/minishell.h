/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:57:42 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/10 16:16:42 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../lib/libft/libft.h"
# include "parsing/p_utils/parsing_utils.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
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

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

typedef struct s_functions
{
	char	*name;
	bool	builtin;
	int		(*func)(void);
	char	*fct_path;

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
	bool			echo_opt;
	char			**args;
	t_redir_token	*redirs;
}	t_commands;

typedef struct s_data
{
	char		*prompt;
	t_parsing	pars;
	t_commands	*cmds;
	char		**environ;

}	t_data;

int		parsing(t_data *data, char *line);
int		lexer(t_data *data, char *line);
int		searcher(t_data *data);

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