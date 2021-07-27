/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:42:37 by mvaldes           #+#    #+#             */
/*   Updated: 2021/07/27 14:35:45 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../minishell.h"

// void	wrong_input(t_data *data)
// {
// 	int	i;

// 	i = 0;
// 	if (data->s_tokens.tk_lst != NULL && \
// 	data->s_tokens.tk_lst[i].token_ptr[0] != '\0')
// 	{
// 		while (i < data->s_tokens.tk_nbr)
// 		{
// 			printf("free: \"%s.\"\n", data->s_tokens.tk_lst[i].token_ptr);
// 			free(data->s_tokens.tk_lst[i].token_ptr);
// 			i++;
// 		}
// 		if (data->s_tokens.tk_lst != NULL)
// 			free(data->s_tokens.tk_lst);
// 	}
// 	ft_putstr_fd("Error\n", STDERR);
// }
