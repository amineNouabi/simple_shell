#include "shell.h"

/**
 * str_numeric - checks if string is numeric
 * @str: string to check
 *
 * Return: 1 if numeric, 0 if not
 */
int str_numeric(char *str)
{
	int i;

	if (!str)
		return (0);

	for (i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}

	return (1);
}

/**
 * replace_string - Replaces first token of input str with another str
 * @input: Input string to change
 * @replacement: replacement to use
 *
 * Return: new string on success, NULL on failure
*/

char *replace_string(char *input, char *replacement)
{
	char *token, *temp, *result = NULL, *delimiter = " \t\n";
	int result_len = 0, token_len;

	temp = strdup(input);
	token = strtok(temp, delimiter);
	while (token)
	{
		if (result == NULL)
		{
			result = strdup(replacement);
			result_len = strlen(result);
		}
		else
		{
			token_len = strlen(token);
			result = realloc(result, result_len + token_len + 2);
			if (!result)
			{
				free(result);
				free(temp);
				free(input);
				return (NULL);
			}
			strcat(result, " ");
			strcat(result, token);
			result_len += token_len + 1;
		}
		token = strtok(NULL, delimiter);
	}
	free(temp);
	free(input);
	return (result);
}
