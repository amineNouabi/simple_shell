#include "shell.h"

/**
 * execute - executes command in child process
 * @full_path: command to execute
 * @cmd: complete command line
 * @allocated: flag variable that keeps track if memory allocated to full_path
 *
 * Return: exit status
 */

int execute(char *full_path, char **cmd, int allocated)
{
	pid_t pid;
	int *status = NULL;

	pid = fork();

	if (pid == 0)
	{
		if (execve(full_path, cmd, environ) == -1)
		{
			if (allocated)
				free(full_path);
			free2darray(cmd);
			return (1);
		}
		if (allocated)
			free(full_path);
		free2darray(cmd);
		return (0);
	}
	else if (pid > 0)
		wait(status);
	else
	{
		perror("fork");
		if (allocated)
			free(full_path);
		free2darray(cmd);
		return (1);
	}
	if (allocated)
		free(full_path);
	free2darray(cmd);
	return (0);
}
