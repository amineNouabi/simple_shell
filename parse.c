#include "shell.h"

/**
 * parse - parses command
 * @cmd: command to parse
 *
 * Return: parsed command
 */

char **parse(char *cmd)
{
	char *delimiter, *token, **tokens = NULL;
	int i = 0;

	delimiter = " \t\n";
	token = strtok(cmd, delimiter);

	while (token)
	{
		i++;
		tokens = realloc(tokens, (i + 1) * sizeof(char *));
		if (!tokens)
		{
			perror("realloc");
			exit(1);
		}
		tokens[i - 1] = token;
		token = strtok(NULL, delimiter);
	}
	tokens[i] = NULL;
	return (tokens);
}

