/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/30 17:09:28 by fcavillo         ###   ########.fr       */
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
int     piping(t_data *data, int cmd_nb);
int	    execute_one(t_data *data, int i);
int	    ft_fork(t_data *data, int i, pid_t *pid);



#endif
