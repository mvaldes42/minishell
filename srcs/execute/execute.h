/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/12 14:25:30 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

int	builtin_cd(char **args);
int	builtin_echo(char **args);
int	builtin_env(char **args);
int	builtin_exit(char **args);
int	builtin_export(char **args);
int	builtin_pwd(char **args);
int	builtin_unset(char **args);

#endif