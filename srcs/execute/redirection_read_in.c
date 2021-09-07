/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_read_in.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 15:18:06 by fcavillo          #+#    #+#             */
/*   Updated: 2021/09/07 18:34:49 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
int	remove_here_doc()
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		
	}
}
*/
int	exec_read_in(t_data *data, int i)
{
	char	*line;
	int	pid[2];
	int	fd[2];
	char *end;
	size_t	len;
	t_commands	cmd;

	
	cmd = data->cmds[i];
	end = data->cmds[i].redirs->filename;
	len = ft_strlen(end);
	printf("end = %s\n", end);
	fd[1] = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0777); // open/create a file
	fd[0] = open("here_doc", O_RDONLY, 0777);
	pid[0] = fork();
	if (pid[0] == 0)
	{
		close(fd[0]);
		line = readline("> ");
		if (ft_strlen(line) < len) //to avoid segfaults
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
	waitpid(pid[0], NULL, 0);
	pid[1] = fork();
	if (pid[1] == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		
		execve(cmd.fct.fct_path, cmd.args, data->environ);
		exit(0);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[1], NULL, 0);
	//remove_here_doc();
	return (0);
}