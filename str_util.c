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

	for (i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}

	return (1);
}
