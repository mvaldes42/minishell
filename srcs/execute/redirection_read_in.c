/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_read_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:18:06 by fcavillo          #+#    #+#             */
/*   Updated: 2021/10/05 21:13:24 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//handle each error
//check if here_doc should be cleared before being unlinked
//check why there is stuff related to stdouts downstairs

/*
** Creates an empty here_doc file in the current repo
*/

int	create_here_doc(void)
{
	int	fd;

	fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (0);
	return (fd);
}

/*
** Assigns \n to ^C
** Compares each line with end
** Copies it in here_doc if != end
** Stops if == end 
*/

void	fill_here_doc(char *end, int heredoc_fd)
{
	char	*line;
	size_t	len;

	signal(SIGINT, sig_heredoc);
	while (1)
	{
		line = readline("> ");
		len = ft_strlen(end);
		if (!line)
		{
			exit (0);
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
** Saves the current stdout, switches to terminal stdout ?
** 
** Fills here_doc from terminal lines, sets it as stdin, removes it
*/

void	exec_read_in(char *end, int *initial_fd)
{
	int	heredoc_fd;
	int	pid;
	int	status;
//	int	fd_stdout;
	(void)initial_fd;
	signal(SIGINT, SIG_IGN);
	heredoc_fd = create_here_doc();
//	fd_stdout = dup(STDOUT_FILENO);
//	dup2(initial_fd[1], STDOUT_FILENO);
	pid = fork();
	if (pid == 0)
		fill_here_doc(end, heredoc_fd);
	waitpid(pid, &status, 0);
/*	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		clear_tmp_file_input();
		g_minishell.error_status = 130;
	}*/
	rm_heredoc();
//	dup2(fd_stdout, STDOUT_FILENO);
//	close(fd_stdout);
}
