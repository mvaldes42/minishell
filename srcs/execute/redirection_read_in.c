/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_read_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:18:06 by fcavillo          #+#    #+#             */
/*   Updated: 2021/09/11 09:50:25 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//change $
//clean

/*
** execs the function from the fd[0] heree_doc
*/

int	exec_here_doc(t_data *data, t_commands cmd, int *fd, int *pid)
{
	pid[1] = fork();
	if (pid[1] == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_fct(data); // gerer erreur, int i?? exit does not work
		exit(0);
		(void)cmd;
	}
	return (0);
}

/*
** copies every line entered into the heredoc until the stop word
*/

int	fill_here_doc(int *fd, int *pid, char *end)
{
	size_t	len;
	char	*line;

	len = ft_strlen(end);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(fd[0]);
		line = readline("> ");
		if (ft_strlen(line) < len)
			len = ft_strlen(line);
		while (ft_strncmp(line, end, len + 1) != 0)
		{
			len = ft_strlen(end);
			write(fd[1], line, ft_strlen(line));
			write(fd[1], &"\n", 1);
			line = readline("> ");
			if (ft_strlen(line) < len)
				len = ft_strlen(line);
		}
		close(fd[1]);
		exit(0);
	}
	return (0);
}

/*
** creates a here doc
** fills it with fill_here_doc
** execs the function with it's content
** deletes it with unlink
*/

int	exec_read_in(t_data *data, int i)
{
	int			pid[2];
	int			fd[2];
	char		*end;
	t_commands	cmd;

	cmd = data->cmds[i];
	end = data->cmds[i].redirs->filename;
	fd[1] = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	fd[0] = open("here_doc", O_RDONLY, 0777);
	fill_here_doc(fd, pid, end);
	waitpid(pid[0], NULL, 0);
	exec_here_doc(data, cmd, fd, pid);
	waitpid(pid[1], NULL, 0);
	close(fd[0]);
	close(fd[1]);
	unlink("here_doc");
	return (0);
}
