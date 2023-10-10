#include "shell.h"

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

		exit_status = execute(cmd, av, count);
	}
	return (exit_status);
}
