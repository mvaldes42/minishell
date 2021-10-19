/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/19 11:14:34 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

int		builtin_cd(char **args, int argc, char ***environ_var);
int		builtin_echo(char **args, int argc, char ***environ_var);
int		builtin_env(char **args, int argc, char ***environ_var);
int		builtin_export(char **args, int argc, char ***environ_var);
int		builtin_pwd(char **args, int argc, char ***environ_var);
int		builtin_unset(char **args, int argc, char ***environ_var);
int		builtin_exit(char **args, int argc, char ***environ_var);

void	free_split(char **split);
int		is_name_valid(char *str);

int		handle_signals_empty(void);
void	handle_signals_exec(void);
void	sig_heredoc(int sig);
void	sig_handler(int sig);
void	sig_quit(int sig);
int		navigate_line(t_data *data);
void	save_fds(int *fd);
int		set_back_fds(int *fd);
int		create_files(t_data *data);
int		make_redirects(t_data *data, int rank, int *initial_fd);
int		exec_read_in(char *end, int *initial_fd);
int		execute(t_data *data, int nb);

#endif
