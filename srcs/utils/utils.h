/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:46:54 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/30 19:05:59 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include "../minishell.h"

void	exit_fail(t_data *data);
void	exit_sucess(t_data *data, char *line);
void	clear_data(t_data *data);
void	print_prompt(void);

int		delim_token_count(char *str, char *separators);
int		char_occu(char *str, char c);
char	*ft_strtok(char *s, const char *delim);

#endif
