/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2021/08/12 16:38:19 by fcavillo         ###   ########.fr       */
=======
=======
>>>>>>> pwd changed args
<<<<<<< HEAD
/*   Updated: 2021/08/12 14:25:30 by mvaldes          ###   ########.fr       */
=======
/*   Updated: 2021/08/12 12:36:30 by fcavillo         ###   ########.fr       */
>>>>>>> pwd
<<<<<<< HEAD
>>>>>>> pwd
=======
=======
/*   Updated: 2021/08/12 14:24:27 by fcavillo         ###   ########.fr       */
>>>>>>> pwd changed args
>>>>>>> pwd changed args
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

<<<<<<< HEAD
#include "../minishell.h"

=======
<<<<<<< HEAD
>>>>>>> pwd changed args
int	builtin_cd(char **args);
int	builtin_echo(char **args);
int	builtin_env(char **args);
int	builtin_exit(char **args);
int	builtin_export(char **args);
int	builtin_pwd(char **args);
int	builtin_unset(char **args);
=======
#include "../minishell.h"

void	builtin_cd(char **args);
void	builtin_echo(char **args);
void	builtin_env(char **args);
void	builtin_exit(char **args);
void	builtin_export(char **args);
void	builtin_pwd(char **args);
void	builtin_unset(char **args);
>>>>>>> pwd changed args

#endif