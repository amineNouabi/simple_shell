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


extern int exit_status;

char *prompt();
char **parse(char *cmd, char *delimiter);
int execute(char **cmd, char **av, int count);
void free2darray(char **arr);
char *check_path(char *command);
void print_env(void);

#endif /*SHELL_H*/
