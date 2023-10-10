#include "shell.h"

/**
 * execute - executes command in child process
 * @cmd: complete command line
 * @av: command line arguments
 * @count: keeps track of how many times shell was executed
 * Return: exit status
 */

int execute(char **cmd, char **av, int count)
{
	pid_t pid;
	int status;
	char *full_path;

	full_path = check_path(cmd[0]);
	if (!full_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", av[0], count, cmd[0]);
		free2darray(cmd);
		return (127);
	}

	pid = fork();

	if (pid == 0)
	{
		if (execve(full_path, cmd, environ) == -1)
		{
			free(full_path);
			free2darray(cmd);
			return (127);
		}
		free(full_path);
		free2darray(cmd);
		return (0);
	}
	else if (pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			free(full_path);
			free2darray(cmd);
			return (WEXITSTATUS(status));
		}
	}
	else
	{
		perror("fork");
		free(full_path);
		free2darray(cmd);
		return (1);
	}
	free(full_path);
	free2darray(cmd);
	return (WEXITSTATUS(status));
}
