#include "shell.h"

/**
 * main - Entry point
 * @ac: Number of command line arguments
 * @av: array of command line arguments
 * Return: 0 on success, 1 on failure
 */

int main(int ac, char **av)
{
	char **cmd, *full_path, *delimiter = " \t\n";
	int allocated;
	int count = 0;

	(void)ac;
	(void)av;

	while (1)
	{
		cmd = parse(prompt(), delimiter);
		count++;
		if (!cmd)
			continue;
		full_path = check_path(cmd[0], &allocated);
		if (!full_path)
		{
			fprintf(stderr, "%s: %d: %s: not found\n", av[0], count, cmd[0]);
			free2darray(cmd);
			continue;
		}
		execute(full_path, cmd, allocated);
	}
	return (0);
}
