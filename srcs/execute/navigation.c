/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:24:14 by fcavillo          #+#    #+#             */
/*   Updated: 2021/09/30 16:14:52 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
check if there are redirs, send files to be created
send fds to be redirected
check if pipe, send them to be created and to redirect fds
send commands to be exec 
*/

int	ft_create_files(t_data *data)
{
	
}

int navigate_line(t_data *data)
{
	if (check_redir(data))
	{
		ft_create_files(data);
	}
	return (1);
}

