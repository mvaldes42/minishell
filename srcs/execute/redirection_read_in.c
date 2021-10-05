/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_read_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:18:06 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/05 18:39:46 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//change $
//clean

int	create_here_doc(void)
{
	int	fd;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (0); //error
	return (fd);
}

void	fill_here_doc(char *end, int heredoc_fd)
{
	char	*line;
	size_t	len;

	//sig?
	len = ft_strlen(end);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			exit (0); //error
		}
		if (ft_strlen(line) < len)
			len = ft_strlen(line);
		if (ft_strncmp(line, end, len + 1) != 0)
			ft_putendl_fd(line, heredoc_fd);
		else
		{
			close(heredoc_fd);
			free(line);
			break ;
		}
		free(line);
	}
	exit (0);
}

void	rm_heredoc(void)
{
	int	heredoc_fd;

	heredoc_fd = open("here_doc", O_RDONLY);
	unlink("here_doc");
	dup2(heredoc_fd, STDIN_FILENO);
	close(heredoc_fd);
}

/*
void	clear_tmp_file_input(void) //needed ?
{
	int		tmp_fd;

	tmp_fd = open("here_doc", O_WRONLY | O_TRUNC, 0600);
	close(tmp_fd);
}
*/

void	exec_read_in(char *end, int *initial_fd)
{
	int	heredoc_fd;
	int	fd_stdout;
	int	pid;
	int	status;

	heredoc_fd = create_here_doc();
	fd_stdout = dup(STDOUT_FILENO);
	dup2(initial_fd[1], STDOUT_FILENO);
	//sig
	pid = fork();
	if (pid == 0)
		fill_here_doc(end, heredoc_fd);
	waitpid(pid, &status, 0); //status ??
//	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)///////////
//	{
//		clear_tmp_file_input();
//		g_minishell.error_status = 130;
//	}	
	rm_heredoc();
	dup2(fd_stdout, STDOUT_FILENO);
	close(fd_stdout);
}
