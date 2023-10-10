#include "shell.h"

int exit_status = 0;

/**
 * main - Entry point
 * @ac: Number of command line arguments
 * @av: array of command line arguments
 * Return: 0 on success, 1 on failure
 */
int main(int ac, char **av)
{
	char **cmd, *delimiter = " \t\n";
	int count = 0;

	(void)ac;
	(void)av;

	while (1)
	{
		cmd = parse(prompt(), delimiter);
		count++;
		if (!cmd)
			continue;

		if (strcmp(cmd[0], "env") == 0)
			print_env();
		else if (strcmp(cmd[0], "exit") == 0)
		{
			free2darray(cmd);
			exit(exit_status);
		}
		else
			exit_status = execute(cmd, av, count);
		free2darray(cmd);
	}
	return (exit_status);
}
