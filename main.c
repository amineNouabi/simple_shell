#include "shell.h"

/**
 * main - Entry point
 *
 * Return: 0 on success, 1 on failure
 */

int main(void)
{
	char **cmd;
	int *status = NULL;
	pid_t pid;

	while (1)
	{
		cmd = parse(prompt());
		pid = fork();
		if (pid == 0)
		{
			if (execve(cmd[0], cmd, NULL) == -1)
			{
				perror("./hsh");
				free(cmd); 
				exit(1);
			}
			exit(0);
		}
		else if (pid > 0)
			wait(status);
		else
		{
			perror("fork");
			free(cmd);
			exit(1);
		}
		free(cmd);
	}
	return (0);
}
