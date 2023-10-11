#include "shell.h"

/**
 * update_env_pid - updates the $$ variable
 * @pid: pid of the shell
 * 
 * Return: void
 */
void update_env_pid(int pid)
{
	char *pid_s = NULL, **parsed_cmd = NULL;

	pid_s = malloc(sizeof(char) * 10);
	if (!pid_s)
	{
		perror("Error: ");
		exit(1);
	}
	sprintf(pid_s, "%d", pid);
	parsed_cmd = malloc(sizeof(char *) * 4);
	if (!parsed_cmd)
	{
		perror("Error: ");
		exit(1);
	}
	parsed_cmd[0] = strdup("setenv");
	parsed_cmd[1] = strdup("$");
	parsed_cmd[2] = pid_s;
	parsed_cmd[3] = NULL;

	set_env(parsed_cmd);
	free2darray(parsed_cmd);
}

/**
 * update_env_status - updates the $? variable
 * @pid: pid of the shell
 * 
 * Return: void
 */
void update_env_status()
{
	char *cmd = NULL, **parsed_cmd = NULL;

	cmd = malloc(sizeof(char) * 20);
	if (!cmd)
	{
		perror("Error: ");
		exit(1);
	}
	sprintf(cmd, "setenv ? %d", exit_status);
	parsed_cmd = parse(cmd, " ");
	set_env(parsed_cmd);
	free2darray(parsed_cmd);
}
