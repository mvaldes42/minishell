/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/08/17 11:07:19 by mvaldes          ###   ########.fr       */
=======
/*   Updated: 2021/08/22 16:39:09 by fcavillo         ###   ########.fr       */
>>>>>>> pipes stuck at number 2
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

int		builtin_cd(char **args);
int		builtin_echo(char **args);
int		builtin_env(char **args);
int		builtin_export(char **args);
int		builtin_pwd(char **args);
int		builtin_unset(char **args);
int		builtin_exit(char **args);

void	free_split(char **split);
int     piping(t_data *data, int cmd_nb);

#endif
