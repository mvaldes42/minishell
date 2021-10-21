/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:55:43 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/21 14:59:42 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_UTILS_H
# define GENERAL_UTILS_H

# include "../minishell.h"

# define RL_S "\1"
# define RL_E "\2"
# define P_ESC_SEQ "\1\033[0m\2"

typedef enum e_err_codes
{
	MISSING_QUOTE = 132,
	VAR_NOT_FOUND = 133,
	CMD_NOT_FOUND = 127,
	UNEXPECTED_TK = 135,
	EMPTY_LINE = 136,
	INV_NAME = 137,
	HOME_NSET = 138,
	FUNCT_NULL = 139,
	UNSET_NOT_FOUND = 140,
}	t_err_codes;

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