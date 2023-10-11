#include "shell.h"

/**
 * free2darray - Frees a 2D array
 * @arr: array to free
 *
 * Return: void
 */

void free2darray(char **arr)
{
	int i, count = 0;

	if (!arr)
		return;

	while (arr[count] != NULL)
		count++;

	for (i = 0; i < count; i++)
		free(arr[i]);
	free(arr);
}

/**
 * arr_len - returns the length of an array
 * @arr: array to check
 *
 * Return: length of array
 */
int arr_len(char **arr)
{
	int i;

	if (!arr)
		return (0);

	i = -1;
	while (arr[++i])
		;
	return (i);
}
