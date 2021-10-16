/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:08:43 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/15 15:09:25 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	term_interactive(void)
{
	struct termios	term1;

	tcgetattr(STDIN_FILENO, &term1);
	term1.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
		return (0);
	return (1);
}

int	term(void)
{
	struct termios	term1;

	tcgetattr(STDIN_FILENO, &term1);
	term1.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
		return (0);
	return (1);
}