/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:46:54 by mvaldes           #+#    #+#             */
/*   Updated: 2021/06/29 19:48:12 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	exit_fail(t_data *data);
void	print_prompt(void);

int	delim_token_count(char *str);
int	char_occu(char *str, char c);
#endif