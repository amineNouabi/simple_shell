#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;
extern int exit_status;

char *prompt();
char **parse(char *cmd, char *delimiter);
int execute(char **cmd, char **av, int count);
char *check_path(char *command);

/** builtins */
void print_env(void);
void exit_shell(char **args, char **argv, int count);
void set_env(char **args, int count, char **argv);
void unset_env(char **args);
int change_directory(char **args, char **av, int count);

/** string utils */
int str_numeric(char *str);

/** array utils */
int arr_len(char **arr);
void free2darray(char **arr);


#endif /*SHELL_H*/
