/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/13 14:25:32 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

int	builtin_cd(char **args);
int	builtin_echo(char **args);
int	builtin_env(char **args);
int	builtin_exit(char **args);
int	builtin_export(char **args);
int	builtin_pwd(char **args);
int	builtin_unset(char **args);

#endif

// 28 PAGER=less
// 29 LESS=-R
// 30 
// 31 

// 28 PAGER=less
// 29 LESS=-R
// 30 =/Users/mvaldes/Desktop/42/CURSUS/minishell/./minishell
