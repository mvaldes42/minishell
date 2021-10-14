/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:57:42 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/14 17:27:49 by fcavillo         ###   ########.fr       */
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
# include <fcntl.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define TRUE 1
# define FALSE 0

typedef struct s_minishell
{
	int			exit_status;
	int			error_status;
	bool		stopped_heredoc;
	
}				t_minishell;

t_minishell	g_minishell;

typedef int	(*t_builtin)(char **args, int argc, char ***environ_var);

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
	int				nbr_args;
	t_redir_token	*redirs;
}	t_commands;

typedef struct s_data
{
	char		*prompt;
	t_parsing	pars;
	t_commands	*cmds;
	char		**environ;
	bool		is_exit;
	bool		in_read;
}	t_data;

int		parsing(t_data *data, char *line);
int		lexer(t_data *data, char *line);

#endif