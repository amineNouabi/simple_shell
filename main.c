#include "shell.h"

/**
 * main - Entry point
 *
 * Return: 0 on success, 1 on failure
 */

int main(void)
{
	char **cmd;
	int *status = NULL, rows;
	pid_t pid;

	while (1)
	{
		cmd = parse(prompt());
		rows = get_num_rows(cmd);
		pid = fork();
		if (pid == 0)
		{
			if (execve(cmd[0], cmd, NULL) == -1)
			{
				perror("./hsh");
				free2darray(cmd, rows);
				exit(1);
			}
			exit(0);
		}
		else if (pid > 0)
			wait(status);
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
