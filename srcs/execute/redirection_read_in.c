/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_read_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:18:06 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/22 15:49:51 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Creates an empty here_doc file in the current repo
*/

int	create_here_doc(void)
{
	int	fd;

	signal(SIGINT, SIG_IGN);
	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		g_error = errno;
		return (-1);
	}
	return (fd);
}

void	heredoc_stdin(t_data *data, char *end, int heredoc_fd, size_t len)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		len = ft_strlen(end);
		if (!line)
		{
			clear_data(data);
			free_environ(data);
			exit (131);
		}
		if (ft_strlen(line) < len)
			len = ft_strlen(line);
		if (ft_strncmp(line, end, len + 1) != 0)
			ft_putendl_fd(line, heredoc_fd);
		else
		{
			close(heredoc_fd);
			ft_free_str(&line);
			break ;
		}
		ft_free_str(&line);
	}	
}

/*
** Assigns \n to ^C
** Compares each line with end
** Copies it in here_doc if != end
** Stops if == end
*/

void	fill_here_doc(t_data *data, char *end, int heredoc_fd)
{
	size_t	len;

	len = 0;
	signal(SIGINT, sig_heredoc);
	heredoc_stdin(data, end, heredoc_fd, len);
	clear_data(data);
	free_environ(data);
	if (g_error == 130)
		exit (130);
	exit (0);
}

/*
** Duplicates here_doc into stdin
** Deletes here_doc
*/

void	rm_heredoc(void)
{
	int	heredoc_fd;

	heredoc_fd = open("here_doc", O_RDONLY);
	unlink("here_doc");
	dup2(heredoc_fd, STDIN_FILENO);
	close(heredoc_fd);
}

/*
** Disables ^C since it would display an excess prompt
** Creates a here_doc in the current repo
** Saves the current stdout
** puts the stdout back to terminal
** Fills here_doc from terminal line
** sets it as stdin, removes it
** puts stdout back to base stdout
** 
*/

int	exec_read_in(t_data *data, char *end, int *initial_fd)
{
	int	heredoc_fd;
	int	pid;
	int	status;
	int	fd_out;

	heredoc_fd = create_here_doc();
	if (heredoc_fd == -1)
		return (0);
	fd_out = dup(STDOUT);
	dup2(initial_fd[1], STDOUT_FILENO);
	pid = fork();
	if (pid == -1)
	{
		g_error = errno;
		return (0);
	}
	if (pid == 0)
		fill_here_doc(data, end, heredoc_fd);
	waitpid(pid, &status, 0);
	rm_heredoc();
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	check_heredoc_ctrl_d(status, end);
	return (1);
}
