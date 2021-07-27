/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 15:55:43 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/27 15:56:21 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_UTILS_H
# define GENERAL_UTILS_H
# include "../minishell.h"

void	exit_sucess(t_data *data, char *line);
void	clear_data(t_data *data);
void	create_prompt(t_data *data);
int		char_occu(char *str, char c);

#endif