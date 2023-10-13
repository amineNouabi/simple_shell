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
 * parse_alias - Tokenize a string based on certain delimiters.
 * @str: The string to tokenize.
 *
 * Return: An array of strings (tokens).
 */
char **parse_alias(const char *str)
{
	int i, j, len, start, end, k;
	char **tokens;

	i = 0;
	j = 0;
	len = strlen(str);
	tokens = malloc(sizeof(char *) * (len + 1));
	if (!tokens)
		return (NULL);
	while (i < len)
	{
		while ((str[i] == ' ' || str[i] == '\n') && i < len)
			i++;
		start = i;
		while (str[i] && str[i] != ' ' && str[i] != '=' && str[i] != '\n')
			i++;
		if (str[i] == '=')
		{
			i++;
			if (str[i] == '"')
			{
				i++;
				while (str[i] && str[i] != '"')
					i++;
				if (str[i])
					i++;
			}
		}
		end = i;
		while ((str[end - 1] == ' ' || str[end - 1] == '\n') && end > start)
			end--;
		if (end - start > 0)
		{
			tokens[j] = malloc(end - start + 1);
			if (!tokens[j])
			{
				for (k = 0; k < j; k++)
					free(tokens[k]);
				free(tokens);
				return (NULL);
			}
			strncpy(tokens[j], &str[start], end - start);
			tokens[j][end - start] = '\0';
			j++;
		}
	}
	tokens[j] = NULL;
	return (tokens);
}
