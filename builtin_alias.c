#include "shell.h"

int n_alias;

/**
 * handle_alias - handles builtin alias command
 * @cmd: arguments passed
 *
 * Return: void
 */

void handle_alias(char **cmd)
{
	int i, j, found;

	if (!cmd[1])
	{
		for (i = 0; alias_list[i]; i++)
			printf("%s=\'%s\'\n", alias_list[i]->name, alias_list[i]->value);
		return;
	}
	else
	{
		for (i = 1; cmd[i]; i++)
		{
			if (strchr(cmd[i], '='))
				store_alias(cmd[i]);
			else
			{
				found = 0;
				for (j = 0; alias_list[j]; j++)
				{
					if (strcmp(cmd[i], alias_list[j]->name) == 0)
					{
						printf("%s=\'%s\'\n", alias_list[j]->name, alias_list[j]->value);
						found = 1;
						break;
					}
				}
				if (!found)
					printf("%s: %s not found\n", cmd[0], cmd[i]);
			}
		}
	}
}

/**
 * store_alias - Stores aliases
 * @cmd: arguments passed
 *
 * Return: void
*/

void store_alias(char *cmd)
{
	int i, found;
	alias_t *new_alias;

	new_alias = create_alias(cmd);
	found = 0;
	for (i = 0; i < n_alias; i++)
	{
		if (strcmp(alias_list[i]->name, new_alias->name) == 0)
		{
			free(alias_list[i]->value);
			alias_list[i]->value = new_alias->value;
			free(new_alias->name);
			free(new_alias);
			found = 1;
			break;
		}
	}
	if (!found)
	{
		alias_list[n_alias++] = new_alias;
		alias_list[n_alias] = NULL;
	}
}

/**
 * create_alias - Creates a new alias
 * @arg: argument passed
 * Return: created alias (alias_t)
*/

alias_t *create_alias(char *arg)
{
	char name[50], value[100];
	char *equals, *quote_start, *quote_end;
	int n;
	alias_t *alias;

	alias = malloc(sizeof(alias_t));
	if (!alias)
		return (NULL);

	equals = strchr(arg, '=');
	n = equals - arg;
	strncpy(name, arg, n);
	name[n] = '\0';

	quote_start = strchr(arg, '\"');
	quote_end = strrchr(arg, '\"');
	n = quote_end - quote_start - 1;
	strncpy(value, quote_start + 1, n);
	value[n] = '\0';

	alias->name = strdup(name);
	if (!alias->name)
	{
		free(alias);
		return (NULL);
	}
	alias->value = strdup(value);
	if (!alias->value)
	{
		free(alias->name);
		free(alias);
		return (NULL);
	}
	return (alias);
}

/**
 * free_alias - frees all stored aliases
 * @arr: alias array
 *
 * Return: void
*/

void free_alias(alias_t **arr)
{
	int i = 0;

	while (arr[i] != NULL)
	{
		free(arr[i]->name);
		free(arr[i]->value);
		free(arr[i]);
		i++;
	}
}