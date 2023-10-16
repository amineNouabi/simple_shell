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

	replace_aliases(&cmd, delimiter);
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
 * replace_aliases - Replaces alias in command by its value
 * @cmd: input command to replace
 * @delimiter: delimiter to tokenize command
 *
 * Return: void
*/

void replace_aliases(char **cmd, char *delimiter)
{
	char *temp, *token;
	int k, l, flag;

	temp = strdup(*cmd);
	token = strtok(temp, delimiter);
	for (k = 0; alias_list[k]; k++)
	{
		flag = 0;
		if (strcmp(token, alias_list[k]->name) == 0)
		{
			for (l = 0; alias_list[l]; l++)
			{
				if (strcmp(alias_list[k]->value, alias_list[l]->name) == 0)
				{
					*cmd = replace_string(*cmd, alias_list[l]->value);
					flag = 1;
					break;
				}
			}
			if (!flag)
				*cmd = replace_string(*cmd, alias_list[k]->value);
			break;
		}
	}
	free(temp);
}

