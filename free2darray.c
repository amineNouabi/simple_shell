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
