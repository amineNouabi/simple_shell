#include "shell.h"

/**
 * main - Entry point
 * @ac: Number of command line arguments
 * @av: array of command line arguments
 * Return: 0 on success, 1 on failure
 */

int main(int ac, char **av)
{
	char **cmd;
	int *status = NULL, rows;
	pid_t pid;

	(void)ac;

	while (1)
	{
		cmd = parse(prompt());
		rows = get_num_rows(cmd);
		pid = fork();
		if (pid == 0)
		{
			if (execve(cmd[0], cmd, environ) == -1)
			{
				perror(av[0]);
				free2darray(cmd, rows);
				exit(1);
			}
			free2darray(cmd, rows);
			exit(0);
		}
		else if (pid > 0)
		{
			wait(status);
		}
		else
		{
			perror("fork");
			free2darray(cmd, rows);
			exit(1);
		}
		free2darray(cmd, rows);
	}
	return (0);
}
