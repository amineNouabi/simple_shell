#include "shell.h"

/**
 * prompt - Displays prompt to input command
 *
 * Return: buffer (string);
 */

char *prompt()
{
	char *buffer = NULL;
	size_t buffer_size = 0;
	int n_chars;

	if (isatty(STDIN_FILENO))
		write(1, "$ ", 2);
	n_chars = getline(&buffer, &buffer_size, stdin);

	if (n_chars == EOF)
	{
		if (isatty(STDIN_FILENO))
			write(1, "\n", 1);
		free(buffer);
		exit(exit_status);
	}
	else if (n_chars == 0)
	{
		free(buffer);
		exit(exit_status);
	}

	/*if (strcmp(buffer, "exit\n") == 0)
	//{
	//	free(buffer);
	//	exit(exit_status);
	}
	*/
	return (buffer);
}
