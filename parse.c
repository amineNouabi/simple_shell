#include "shell.h"

/**
 * parse - parses command
 * @cmd: command to parse
 *
 * Return: parsed command
 */

char **parse(char *cmd)
{
	char *delimiter, *temp = NULL, *token = NULL, **tokens = NULL;
	int i = 0, j = 0;

	delimiter = " \t\n";
	temp = strdup(cmd);
	token = strtok(temp, delimiter);
	while (token)
	{
		i++;
		token = strtok(NULL, delimiter);
	}
	free(temp);

	tokens = malloc(sizeof(char *) * (i + 1));
	if (!tokens)
	{
		free(cmd);
		return (NULL);
	}

	token = strtok(cmd, delimiter);
	while (token)
	{
		tokens[j] = strdup(token);
		token = strtok(NULL, delimiter);
		j++;
	}
	free(cmd);
	tokens[j] = NULL;
	return (tokens);
}

