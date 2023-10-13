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

/*Structs*/

typedef struct alias
{
  char *name;
  char *value;
} alias_t;

extern char **environ;
extern int exit_status;
extern alias_t *alias_list[50];
extern int n_alias;

/*Command processing*/
char *prompt();
char **parse(char *cmd, char *delimiter);
char **parse_alias(char *cmd);
int execute(char **cmd, char **av, int count);
char *check_path(char *command);

/** builtins */
void print_env(void);
void exit_shell(char **args, char **argv, int count);
void set_env(char **args);
void unset_env(char **args);
int change_directory(char **args, char **av, int count);
void handle_alias(char **cmd);
alias_t *create_alias(char *arg);
void store_alias(char *cmd);
void free_alias(alias_t **arr);

void update_env_status();
void update_env_pid(int pid);

/** string utils */
int str_numeric(char *str);

/** array utils */
int arr_len(char **arr);
void free2darray(char **arr);

#endif /*SHELL_H*/
