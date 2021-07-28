/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramdani <cramdani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 17:50:41 by cramdani          #+#    #+#             */
/*   Updated: 2021/07/28 18:32:56 by cramdani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int i = 0;
	// execv("/bin/ls", "");
	while (env[i + 1] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}