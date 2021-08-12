/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/08/12 16:38:19 by fcavillo         ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2021/08/12 14:25:30 by mvaldes          ###   ########.fr       */
=======
/*   Updated: 2021/08/12 12:36:30 by fcavillo         ###   ########.fr       */
>>>>>>> pwd
>>>>>>> pwd
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "../minishell.h"

int	builtin_cd(char **args);
int	builtin_echo(char **args);
int	builtin_env(char **args);
int	builtin_exit(char **args);
int	builtin_export(char **args);
int	builtin_pwd(char **args);
int	builtin_unset(char **args);

#endif