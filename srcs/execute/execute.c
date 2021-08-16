/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcavillo <fcavillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:27:17 by mvaldes           #+#    #+#             */
/*   Updated: 2021/08/16 16:24:42 by fcavillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../minishell.h"

int		piping(t_data *data)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];
		(void)	data;
        pipe(fd);
        
        if((childpid = fork()) == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid == 0)
        {
                /* Child process closes up input side of pipe */
                close(fd[0]);

                /* Send "string" through the output side of pipe */
                write(fd[1], string, (strlen(string)+1));
                exit(0);
        }
        else
        {
                /* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("Received string: %s", readbuffer);
        }
        
        return(0);
}

/*{
	int		fd[2];
	pid_t   childpid;

	(void)data;
	pipe(fd);
	childpid = fork(); //sets child pid to 0 first passage
	if (childpid == -1) // if error
		return (0);
	if (childpid == 0)
	{
		// Child process closes up input side of pipe 
		close(fd[0]);
	}
	else
	{
		// Parent process closes up output side of pipe 
		close(fd[1]);
	}	
	return (1);	
}*/

int		builtouts(t_data *data, t_commands cmd)
{
	pid_t	pid;
	pid_t	wpid;
	int		status;

	piping(data);
	printf("done\n");
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