/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:55:43 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/27 16:49:11 by mvaldes          ###   ########.fr       */
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
	CMD_NOT_FOUND = 134,
	UNEXPECTED_TK = 135,
	EMPTY_LINE = 136,
	INV_NAME = 137,
}	t_err_codes;

typedef struct s_data		t_data;

void		ft_free(void *ptr);
int			error_handling(void);
void		clear_data(t_data *data);
void		create_prompt(t_data *data, int fail);
int			char_occu(char *str, char c);
void		free_environ(t_data *data);

#endif