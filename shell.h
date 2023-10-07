#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

char *prompt();
char **parse(char *cmd);
void free2darray(char **arr, int rows);
int get_num_rows(char **arr);


void print_array(char *a);
void print_2darray(char **a);

#endif /*SHELL_H*/
