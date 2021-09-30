/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
/*   Updated: 2021/09/30 13:41:44 by fcavillo         ###   ########.fr       */
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
int		execute_piped_fct(t_data *data, int i);
int		ft_fork(t_data *data, int i, pid_t *pid);
int		check_redir(t_data *data);
int		exec_read_in(t_data *data, int i);
int		execute_fct(t_data *data);
void	check_tty(void);
void	sig_handler(int sig);
int     term(void);
int		ft_new_stdin(int fd);
int		ft_new_stdout(int fd);
int		handle_signals(void);
int     navigate_line(t_data *data);




#endif
