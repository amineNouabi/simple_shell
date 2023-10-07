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

	write(1, "$ ", 2);
	n_chars = getline(&buffer, &buffer_size, stdin);

	printf("\nn_chars: %d\n", n_chars);
	print_array(buffer);
	printf("\n");

	if (n_chars == EOF)
	{
		perror("End of file");
		free(buffer);
		exit(1);
	}
	else if (n_chars == 0)
	{
		free(buffer);
		exit(0);
	}

	if (strcmp(buffer, "exit\n") == 0)
	{
		free(buffer);
		exit(0);
	}

	return (buffer);
}
