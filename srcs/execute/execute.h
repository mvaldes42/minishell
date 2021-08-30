/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/30 15:17:33 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

int		builtin_cd(char **args, char **environ_var);
int		builtin_echo(char **args, char **environ_var);
int		builtin_env(char **args, char **environ_var);
int		builtin_export(char **args, char **environ_var);
int		builtin_pwd(char **args, char **environ_var);
int		builtin_unset(char **args, char **environ_var);
int		builtin_exit(char **args, char **environ_var);

void	free_split(char **split);
int		piping(t_data *data, int cmd_nb);
int		execute_one(t_data *data, int i);

#endif
