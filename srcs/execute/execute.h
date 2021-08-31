/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/31 15:20:35 by mvaldes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

int		builtin_cd(char **args, char ***environ_var);
int		builtin_echo(char **args, char ***environ_var);
int		builtin_env(char **args, char ***environ_var);
int		builtin_export(char **args, char ***environ_var);
int		builtin_pwd(char **args, char ***environ_var);
int		builtin_unset(char **args, char ***environ_var);
int		builtin_exit(char **args, char ***environ_var);

void	free_split(char **split);
int		is_name_valid(char *str);

int		piping(t_data *data, int cmd_nb);
int		execute_one(t_data *data, int i);
int		ft_fork(t_data *data, int i, pid_t *pid);

#endif
