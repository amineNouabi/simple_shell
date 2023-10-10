#include "shell.h"

/**
 * parse - parses command
 * @cmd: command to parse
 * @delimiter: delimiter at which we need to parse
 * Return: parsed command
 */

char **parse(char *cmd, char *delimiter)
{
	char *temp = NULL, *token = NULL, **tokens = NULL;
	int i = 0, j = 0;

	temp = strdup(cmd);
	token = strtok(temp, delimiter);
	if (!token)
	{
		free(cmd);
		free(temp);
		return (NULL);
	}
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
	tokens[j] = NULL;
	free(cmd);
	return (tokens);
}

