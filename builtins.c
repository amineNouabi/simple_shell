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
			fprintf(stderr, "%s: %d: exit: Illegal number: %s\n",
				argv[0], count, args[1]);
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
 *
 * Return: void
*/
void set_env(char **args)
{
	int len = arr_len(args);
	if (len == 3)
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

/**
 * change_directory - changes directory
 * @args: arguments passed
 * @av: command line arguments passed to main
 * @count: number of shell executions
 * Return: 0 on success, relevant error on failure
 */

int change_directory(char **args, char **av, int count)
{
	char *home_dir, *prev_dir, *current_dir, *new_dir;

	current_dir = getcwd(NULL, 0);
	if (args[1])
	{
		if (strcmp(args[1], "-") == 0)
		{
			prev_dir = getenv("OLDPWD");
			if (!prev_dir)
				prev_dir = current_dir;
			printf("%s\n", prev_dir);
			chdir(prev_dir);
		}
		else if (chdir(args[1]) == -1)
		{
			fprintf(stderr, "%s: %d: %s: can't cd to %s\n",
					av[0], count, args[0], args[1]);
			free(current_dir);
			return (1);
		}
	}
	else
	{
		home_dir = getenv("HOME");
		if (!home_dir)
		{
			free(current_dir);
			return (1);
		}
		chdir(home_dir);
	}
	new_dir = getcwd(NULL, 0);
	setenv("PWD", new_dir, 1);
	setenv("OLDPWD", current_dir, 1);
	free(current_dir);
	free(new_dir);
	return (0);
}

