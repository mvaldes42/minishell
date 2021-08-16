/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 16:27:34 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"

void	testos(char **s)
{
	int i = 0;
	while (i < 3)
	{
		printf("TESTOS : %d = %s\n", i, s[i]);
		i++;
	}
}

int		piping(t_data *data)
{
	int	fd[2]; //0 = read, 1 = write
	int	pid1; //process id from the forks
	int i;
	int	pid2;
	
	i = 0;
	data->pars.cmd_nbr--;
	testos(data->cmds[i].args);

	if (pipe(fd) == -1) //returns 0 if everything's okay
		return (0); //should it return a specific ERRNO ? 
	pid1 = fork(); //first fork
	if (pid1 == 0)
	{ //child pid 1
		close (fd[0]); //closing reading fd since first pipe should not read
		dup2(fd[1], STDOUT_FILENO); // duplicates fd[1] to write on a copy only
		close (fd[1]); // closing writing fd
//		testos(data->cmds[i].args);
		execve(data->cmds[i].fct.fct_path, data->cmds[i].args, data->environ);
	}
	waitpid(pid1, NULL, 0); // waiting for child1 to finish
	// back to parent
	i++;
	pid2 = fork(); //2nd fork for 2nd fct
	if (pid2 == 0)
	{ //child pid 2
		close (fd[1]); //closing writing fd since second  pipe should not read
		dup2(fd[0], STDIN_FILENO); // duplicates fd[1] to write on a copy only
		close (fd[0]); // closing reading fd
		execve(data->cmds[i].fct.fct_path, data->cmds[i].args, data->environ);
	}
	// back to parent
	close(fd[0]);
	close(fd[1]);
	waitpid(pid2, NULL, 0); // waiting for child2 to finish

	return (0);
}

int		builtouts(t_data *data, t_commands cmd)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;
	printf("executing %s\n", cmd.fct.fct_path);
	pid = fork();
	if (pid == 0) 
	{		// Child process
		if (execve(cmd.fct.fct_path, cmd.args, data->environ) == -1) 
	  		return (0);
	} 
	else if (pid < 0)
		return (0);
	else 
  	{     // Parent process
		wpid = waitpid(pid, &status, WUNTRACED); //waiting for a status change
		while (!WIFEXITED(status) && !WIFSIGNALED(status)) //while status is not exit or killed
		  wpid = waitpid(pid, &status, WUNTRACED);
  	}
	return (1);
}

int	execute(t_data *data)
{
	int			i;
	t_commands	cmd;
	extern char	**environ;

	i = 0;
	if (data->pars.cmd_nbr > 1)
		piping(data);
	else
	{
		while (i < data->pars.cmd_nbr)
		{
			cmd = data->cmds[i];
						if (cmd.fct.builtin)
			{
				if (ft_strncmp(cmd.fct.name, "exit", ft_strlen(cmd.fct.name)) == 0)
					data->is_exit = TRUE;
				if (!cmd.fct.builtin_ptr(cmd.args))
					return (0);
			}
			else
			{
				if (builtouts(data, cmd) == 0)
					return (0);
			}
			i++;
		}
	}
	return (1);
}

/*
int
main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buf;

	assert(argc == 2);

	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	cpid = fork();
	if (cpid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (cpid == 0) {    // Le fils lit dans le tube 
		close(pipefd[1]);  // Ferme l'extrémité d'écriture inutilisée

		while (read(pipefd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);

		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);

	} else {                    // Le père écrit argv[1] dans le tube 
		close(pipefd[0]);       // Ferme l'extrémité de lecture inutilisée 
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]);       // Le lecteur verra EOF 
		wait(NULL);             // Attente du fils 
		exit(EXIT_SUCCESS);
	}
}
*/
/*
int main (int argc, char ** argv) {
	int i;

	for( i=1; i<argc-1; i++)
	{
		int pd[2];
		pipe(pd);

		if (!fork()) {
			dup2(pd[1], 1); // remap output back to parent
			execlp(argv[i], argv[i], NULL);
			perror("exec");
			abort();
		}

		// remap output from previous child to input
		dup2(pd[0], 0);
		close(pd[1]);
	}

	execlp(argv[i], argv[i], NULL);
	perror("exec");
	abort();
}*/