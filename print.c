#include "shell.h"
/**
 * print_array - prints an array of characters
 * @a: array to print
 *
 * Return: void
*/
void print_array(char *a)
{
	int i = 0;

	printf("[ ");
	while (a[i])
	{
		printf("%c", a[i]);
		i++;
	}
	printf(" ]\n");
}

/**
 * print_2darray - prints a 2d array of characters
 * @a: array to print
 *
 * Return: void
 */
void print_2darray(char **a)
{
	int i = 0;

	while (a[i])
	{
		print_array(a[i]);
		i++;
	}
}
