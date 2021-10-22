/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:55:43 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/22 11:03:48 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_UTILS_H
# define GENERAL_UTILS_H

# include "../minishell.h"

# define RL_S "\1"
# define RL_E "\2"
# define P_ESC_SEQ "\1\033[0m\2"

typedef enum e_err_parse
{
	MISSING_QUOTE = 300,
	VAR_NOT_FOUND = 301,
	UNEXPECTED_TK = 302,
	EMPTY_LINE = 303,
	FUNCT_NULL = 304,
}	t_err_parse;

typedef enum e_err_exec
{
	UNSET_NOT_FOUND = 500,
	INV_NAME = 501,
	NO_SUCH_FILE = 502,
	BUILTIN_ERR = 503,
	H_NOT_SET = 504,
	CMD_NOT_EXEC = 126,
	CMD_NOT_FOUND = 127,
	TERM_CTRL_C = 130,
}	t_err_exec;

typedef struct s_data		t_data;

// GENERAL_UTILS_2.C
void		free_tks(t_data *data);
void		ft_free_int(int **int_ptr);
void		ft_free_str(char **str_ptr);
void		create_prompt(t_data *data, int fail);
int			error_handling(t_data *data);
char		*ft_getenv(const char *name, char **environ_var);
// GENERAL_UTILS.C
void		clear_data(t_data *data);
int			char_occu(char *str, char c);
void		free_environ(t_data *data);
int			ft_str_in_str(char *str1, char *str2);

#endif