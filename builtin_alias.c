#include "shell.h"

/**
 * handle_alias - handles builtin alias command
 * @cmd: arguments passed
 *
 * Return: void
 */

void handle_alias(char **cmd)
{
	static int n_alias;
	alias_t *new_alias;
	int i, j, found;
	/*Print aliases*/
	if (!cmd[1])
	{
		for (j = 0; alias_list[j]; j++)
			printf("%s=\'%s\'\n", alias_list[j]->name, alias_list[j]->value);
		return;
	}

	/*Store alias*/
	for (i = 1; cmd[i]; i++)
	{
		new_alias = create_alias(cmd[i]);
		found = 0;
		for (j = 0; j < n_alias; j++)
		{
			if (strcmp(alias_list[j]->name, new_alias->name) == 0)
			{
				free(alias_list[j]->value);
				alias_list[j]->value = new_alias->value;
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
