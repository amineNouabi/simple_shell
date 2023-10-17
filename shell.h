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

/**
 * struct alias - Holds alias names and values
 * @name: Alias name
 * @value: Alias value
 *
 * Description: A struct that holds the name and value of an alias
 */
typedef struct alias
{
	char *name;
	char *value;
} alias_t;

extern char **environ;

/*Command processing*/
char *prompt(int exit_status, alias_t **alias_list);
char **parse(char *cmd, char *delimiter, int exit_status,
		int shell_pid, alias_t **alias_list);
void parse_token(char **tokens, char *token, int i,
				 int exit_status, int shell_pid);
void replace_aliases(char **cmd, char *delimiter, alias_t **alias_list);
int execute(char **cmd, char **av, int count);
char *check_path(char *command);
void remove_comments(char *cmd);

/** builtins */
void print_env(void);
void exit_shell(char **args, char **argv, int count,
		int exit_status, alias_t **alias_list);
void set_env(char **args, int *exit_status);
void unset_env(char **args, int *exit_status);
int change_directory(char **args, char **av, int count);
void handle_alias(char **cmd, alias_t **alias_list);
alias_t *create_alias(char *arg);
void store_alias(char *cmd, alias_t **alias_list);
void free_alias(alias_t **arr);

/** string utils */
int str_numeric(char *str);
char *replace_string(char *input, char *replacement);
int str_tokens_length(char *str, char *delimiter);

/** array utils */
int arr_len(char **arr);
void free2darray(char **arr);

#endif /*SHELL_H*/
