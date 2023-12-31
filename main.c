#include "shell.h"

/**
 * main - Entry point
 * @ac: Number of command line arguments
 * @av: array of command line arguments
 * Return: 0 on success, 1 on fastilure
 */
int main(int ac, char **av)
{
	char **cmd, *delimiter = " \t\n", *input;
	int count = 0, shell_pid = getpid(), exit_status = 0;
	alias_t *alias_list[50] = {NULL};

	if (ac == 2)
	{
		execute_file(av[1], av, &exit_status);
		return (exit_status);
	}
	while (1)
	{
		input = prompt(exit_status, alias_list);
		cmd = parse(input, delimiter, exit_status, shell_pid, alias_list);
		count++;
		if (!cmd)
			continue;

		if (strcmp(cmd[0], "alias") == 0)
			handle_alias(cmd, alias_list);
		else if (strcmp(cmd[0], "env") == 0)
			print_env();
		else if (strcmp(cmd[0], "setenv") == 0)
			set_env(cmd, &exit_status);
		else if (strcmp(cmd[0], "unsetenv") == 0)
			unset_env(cmd, &exit_status);
		else if (strcmp(cmd[0], "exit") == 0)
			exit_shell(cmd, av, count, exit_status, alias_list);
		else if (strcmp(cmd[0], "cd") == 0)
			exit_status = change_directory(cmd, av, count);
		else
			exit_status = execute(cmd, av, count);
		free2darray(cmd);
	}
	return (exit_status);
}
