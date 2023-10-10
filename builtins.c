#include "shell.h"

/**
 * exit_shell - exits the shell
 * @args: arguments passed to exit
 * @argv: argv passed to main function
 * @count: number of commands executed
 * Return: void
 */
void exit_shell(char **args, char **argv, int count)
{
	int status = exit_status;

	if (args[1])
	{
		if (str_numeric(args[1]) && atoi(args[1]) >= 0)
			status = atoi(args[1]);
		else
		{
			fprintf(stderr, "%s: %d: exit: Illegal number: %s\n", argv[0], count, args[1]);
			status = 2;
		}
	}
	free2darray(args);
	exit(status);
}

/**
 * print_env - prints the current environment
 * 
 * Return: void
 */
void print_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		write(1, environ[i], strlen(environ[i]));
		write(1, "\n", 1);
	}
}
