/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 17:38:07 by fcavillo         ###   ########.fr       */
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

int		term(void);
int		handle_signals(void);
void	handle_signals_exec(void);
void	sig_heredoc(int sig);

int		navigate_line(t_data *data);

void	save_fds(int *fd);
int 	set_back_fds(int *fd);

int		make_redirects(t_data *data, int rank, int *initial_fd);
int		exec_read_in(char *end, int *initial_fd);

int		execute(t_data *data, int nb);

#endif
