#include "minishell.h"

static int	get_full_path(char *filename, char *pwd, char **full_path)
{
	if (*filename == '/')
		*full_path = gnl_strjoin(NULL, filename);
	else
	{
		*full_path = gnl_strjoin(NULL, pwd);
		*full_path = gnl_strjoin(*full_path, "/");
		*full_path = gnl_strjoin(*full_path, filename);
	}
	return (0);
}

int	check_fd(t_command *command, int input_fd, char *filename)
{
	if (command->output_fd < 0)
	{
		executable_error_print(filename, ": No such file or directory\n", 1);
		return (-1);
	}
	if (input_fd < 0)
	{
		executable_error_print(filename, ": No such file or directory\n", 1);
		if (!(command->redirect_type & PRE_FD))
			command->input_fd = input_fd;
		return (-1);
	}
	else if (command->redirect_type & READ)
	{
		if (command->input_fd > 0)
			close((command->input_fd));
		command->input_fd = input_fd;
	}
	return (0);
}

static int	open_to_write(char *full_path, t_command *command)
{
	int output_fd;

	if (command->redirect_type & APPEND)
	{
		if (command->output_fd > 1  && !(command->redirect_type & PRE_FD))
			close(command->output_fd);
		output_fd = open(full_path, O_CREAT | O_WRONLY | \
				O_APPEND, 0644);
		if (!(command->redirect_type & PRE_FD))
			command->output_fd = output_fd;
	}
	if (command->redirect_type & WRITE)
	{
		if (command->output_fd > 1)
			close(command->output_fd);
		output_fd = open(full_path, O_CREAT | O_WRONLY | \
				O_TRUNC, 0644);
		if (!(command->redirect_type & PRE_FD))
			command->output_fd = output_fd;
	}
	return (0);
}

int	open_file(t_command *command, char *filename, char *pwd)
{
	char	*full_path;
	int		input_fd;

	if (command && filename && pwd)
	{
		input_fd = 0;
		get_full_path(filename, pwd, &full_path);
		open_to_write(full_path, command);
		if (command->redirect_type & READ)
			input_fd = open(full_path, O_RDONLY);
		command->redirect_type = command->redirect_type & ~(NO_FILENAME);
		free(full_path);
		return (check_fd(command, input_fd, filename));
	}
	return (0);
}
