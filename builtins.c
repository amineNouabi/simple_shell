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

/**
 * set_env - sets an environment variable
 * @args: arguments passed to setenv
 * @count: number of commands executed
 * @argv: argv passed to main function
 *
 * Return: void
*/
void set_env(char **args, int count, char **argv)
{
	int len = arr_len(args);
	if (len > 3)
	{
		fprintf(stderr, "%s: %d: %s: Too many arguments\n", argv[0], count, args[0]);
		exit_status = 2;
	}
	else if (len == 3)
	{
		if (setenv(args[1], args[2], 1) == -1)
		{
			perror("setenv");
			exit_status = 2;
		}
	}
}

/**
 * unset_env - unsets an environment variable
 * @args: arguments passed to setenv
 *
 * Return: void
 */
void unset_env(char **args)
{
	int len = arr_len(args);

	if (len == 2 && unsetenv(args[1]) == -1)
	{
		perror("unsetenv");
		exit_status = 2;
	}
}
