#include "shell.h"

/**
 * free2darray - Frees a 2D array
 * @arr: array to free
 * @rows: num of rows
 *
 * Return: void
 */

void free2darray(char **arr, int rows)
{
	int i;

	if (!arr)
		return;

	for (i = 0; i < rows; i++)
		free(arr[i]);
	free(arr);
}

/**
 * get_num_rows - Calculated number of rows in 2d array
 * @arr: array to use
 *
 * Return: number of rows
 */

int get_num_rows(char **arr)
{
	int count = 0;

	while (arr[count] != NULL)
	{
		count++;
	}
	return (count);
}
