#include "../includes/minishell.h"

int open_file(t_command *command, char *filename)
{
	if (command && filename)
	{
		if (command->redirect_type & APPEND)
		{
			if (command->output_fd > 1)
				close(command->output_fd);
			command->output_fd = open(filename, O_CREAT | O_WRONLY |
												O_APPEND, 0644);
		}
		if (command->redirect_type & WRITE)
		{
			if (command->output_fd > 1)
				close(command->output_fd);
			command->output_fd = open(filename, O_CREAT | O_WRONLY |
												O_TRUNC, 0644);
		}
		if (command->redirect_type & READ || command->redirect_type & LIM_READ)
		{
			if (command->input_fd > 1)
				close(command->input_fd);
			command->input_fd = open(filename, O_RDONLY);
		}
		command->redirect_type = command->redirect_type & ~(NO_FILENAME);
		if (command->output_fd < 0 || command->input_fd < 0)
		{
			write(STDOUT_FILENO, "minishell: ", 11);
			write(STDOUT_FILENO, filename, ft_strlen(filename));
			write(STDOUT_FILENO, ": No such file or directory\n", 28);
			return (-1);
		}
	}
	return (0);
}


