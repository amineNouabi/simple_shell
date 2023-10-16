#include "shell.h"

/**
 * parse - parses command
 * @cmd: command to parse
 * @delimiter: delimiter at which we need to parse
 * @exit_status: exit status of the shell
 * @shell_pid: pid of the shell
 *
 * Return: parsed command
 */
char **parse(char *cmd, char *delimiter, int exit_status, int shell_pid)
{
	char *temp = NULL, *token = NULL, **tokens = NULL;
	int i = 0, j = 0;
	remove_comments(cmd);
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
		parse_token(tokens, token, j, exit_status, shell_pid);
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

/**
 * parse_token - parses token and replaces it with its value
 * @tokens: input command to replace
 * @token: token to replace
 * @i: index of token
 * @exit_status: exit status of the shell
 * @shell_pid: pid of the shell
 *
 * Return: void
 */
void parse_token(char **tokens, char *token, int i,
				 int exit_status, int shell_pid)
{
	char *temp = NULL;

	if (strlen(token) > 1 && token[0] == '$')
	{
		if (token[1] == '$' || token[1] == '?')
		{
			temp = malloc(sizeof(char) * 10);
			if (!temp)
			{
				perror("Error: ");
				exit(1);
			}
			sprintf(temp, "%d", token[1] == '$' ? shell_pid : exit_status);
			tokens[i] = temp;
		}
		else if (token[1])
		{
			temp = getenv(token + 1);
			tokens[i] = temp ? strdup(temp) : strdup("");
		}
	}
	else
		tokens[i] = strdup(token);
}

/**
 * remove_comments - removes comments from command
 * @cmd: command to remove comments from
 *
 * Return: void
 */
void remove_comments(char *cmd)
{
	int i = -1;

	while (cmd[++i])
	{
		if (cmd[i] == '#' && (i == 0 || cmd[i - 1] == ' '))
		{
			cmd[i] = '\0';
			break;
		}
	}
}
