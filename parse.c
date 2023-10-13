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
		if (token[0] == '$' && token[1] && token[1] != ' ')
		{
			temp = getenv(token + 1);
			tokens[j] = temp ? strdup(temp) : strdup("");
		}
		else
			tokens[j] = strdup(token);
		token = strtok(NULL, delimiter);
		j++;
	}
	tokens[j] = NULL;
	free(cmd);
	return (tokens);
}

/**
 * parse_alias - Parses alias command
 * @cmd: Command to parse
 *
 * Return: An array of strings (tokens).
 */
char **parse_alias(char *cmd)
{
	int i, j, len, start, end, k;
	char **tokens;

	i = 0;
	j = 0;
	len = strlen(cmd);
	tokens = malloc(sizeof(char *) * (len + 1));
	if (!tokens)
	{
		free(cmd);
		return (NULL);
	}
	while (i < len)
	{
		while ((cmd[i] == ' ' || cmd[i] == '\n') && i < len)
			i++;
		start = i;
		while (cmd[i] && cmd[i] != ' ' && cmd[i] != '=' && cmd[i] != '\n')
			i++;
		if (cmd[i] == '=')
		{
			i++;
			if (cmd[i] == '"')
			{
				i++;
				while (cmd[i] && cmd[i] != '"')
					i++;
				if (cmd[i])
					i++;
			}
		}
		end = i;
		while ((cmd[end - 1] == ' ' || cmd[end - 1] == '\n') && end > start)
			end--;
		if (end - start > 0)
		{
			tokens[j] = malloc(end - start + 1);
			if (!tokens[j])
			{
				for (k = 0; k < j; k++)
					free(tokens[k]);
				free(cmd);
				free(tokens);
				return (NULL);
			}
			strncpy(tokens[j], &cmd[start], end - start);
			tokens[j][end - start] = '\0';
			j++;
		}
	}
	tokens[j] = NULL;
	free(cmd);
	return (tokens);
}
