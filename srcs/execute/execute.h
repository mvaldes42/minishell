/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvaldes <mvaldes@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 18:08:59 by mvaldes           #+#    #+#             */
/*   Updated: 2021/10/12 15:02:55 by mvaldes          ###   ########.fr       */
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
/*int		piping(t_data *data, int cmd_nb);
int		execute_piped_fct(t_data *data, int i);
int		ft_fork(t_data *data, int i, pid_t *pid);
int		check_redir(t_data *data);
int		exec_read_in(t_data *data, int i);
int		execute_fct(t_data *data);
void	check_tty(void);*/
void	sig_handler(int sig);
int     term(void);
int		ft_new_stdin(int fd);
int		ft_new_stdout(int fd);
int		handle_signals(void);

int 	navigate_line(t_data *data);
void    set_initial_fd(int *first_fd);
void    save_fds(int *fd);
void    set_back_fds(int *fd);
void    close_initial_fd(int first_fd);
void	make_redirects(t_data *data, int base_rank, int rank, int *initial_fd);
void	execute(t_data *data, int nb);

#endif
