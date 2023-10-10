#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

char *prompt();
char **parse(char *cmd, char *delimiter);
int execute(char *full_path, char **cmd, int allocated);
void free2darray(char **arr);
char *check_path(char *command, int *allocated);

#endif /*SHELL_H*/
