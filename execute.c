#include "shell.h"

/**
 * execute - executes command in child process
 * @cmd: complete command line
 * @av: command line arguments
 * @count: keeps track of how many times shell was executed
 * Return: exit status
 */

int execute(char **cmd, char **av, int count)
{
	pid_t pid;
	int status;
	char *full_path;

	full_path = check_path(cmd[0]);
	if (!full_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n", av[0], count, cmd[0]);
		return (127);
	}

	pid = fork();

	if (pid == 0)
	{
		if (execve(full_path, cmd, environ) == -1)
		{
			free(full_path);
			return (127);
		}
		free(full_path);
		return (0);
	}
	else if (pid > 0)
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			free(full_path);
			return (WEXITSTATUS(status));
		}
	}
	else
	{
		perror("fork");
		free(full_path);
		return (1);
	}
	free(full_path);
	return (WEXITSTATUS(status));
}

/**
 * execute_file - Executes commands in file line by line
 * @filename: name of file to execute
 * @av: command line arguments passed to program
 * @exit_status: exit status of our program
 *
 * Return: void
 */

void execute_file(char *filename, char **av, int *exit_status)
{
	int fd, i, count = 0;
	char **lines, **command, buffer[1024];
	ssize_t n_read;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "%s: %d: Can't open %s\n", av[0], count, av[1]);
		*exit_status = 127;
		return;
	}
	n_read = read(fd, buffer, sizeof(buffer));
	if (n_read <= 0)
	{
		close(fd);
		*exit_status = 0;
		return;
	}
	buffer[n_read] = '\0';
	lines = parse_file(buffer, "\n");
	for (i = 0; lines[i]; i++)
	{
		command = parse_file(lines[i], " \t\n");
		*exit_status = execute(command, av, count);
		free2darray(command);
	}
	free2darray(lines);
	close(fd);
}
