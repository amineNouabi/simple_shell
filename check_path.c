#include "shell.h"

/**
 * check_path - checks if command exists in path
 * @command: command to check
 * @allocated: flag to keep track if we allocated memory or not
 * Return: cmd path if found, NULL if not found
*/

char *check_path(char *command, int *allocated)
{
	char *path_var, *path, *full_path;
	struct stat st;

	if (command[0] == '/')
	{
		*allocated = 0;
		return (command);
	}

	path_var = strdup(getenv("PATH"));

	path = strtok(path_var, ":");
	while (path)
	{
		full_path = malloc(strlen(path) + strlen(command) + 2);
		strcpy(full_path, path);
		strcat(full_path, "/");
		strcat(full_path, command);
		if (stat(full_path, &st) == 0)
		{
			free(path_var);
			*allocated = 1;
			return (full_path);
		}

		free(full_path);
		path = strtok(NULL, ":");
	}
	free(path_var);
	return (NULL);
}
