#include "../includes/minishell.h"

int open_tmp_file(char *stop_str)
{
	int		fd;
	char 	*curr_line;
	char 	*line;
	int 	ret;
	
	fd = open(TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd > 0)
	{
		line = NULL;
		curr_line = NULL;
		ret = 1;
		while(ret > 0)
		{
			write(STDOUT_FILENO, "> ", 2);
			ret = get_next_line(STDIN_FILENO, &curr_line);
			if (line)
				line = gnl_strjoin(line, "\n");
			line = gnl_strjoin(line, curr_line);
			if (!ft_strncmp(stop_str, curr_line, ft_strlen(curr_line)))
				break ;
			free(curr_line);
			curr_line = NULL;
		}
		write (fd, line, ft_strlen(line));
		write (STDOUT_FILENO, line, ft_strlen(line));
		free(line);
		close(fd);
		fd = open(TMP_FILE, O_RDONLY, 0644);
	}
	return (fd);
}

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
		if (command->redirect_type & READ)
		{
			if (command->input_fd > 1)
				close(command->input_fd);
			command->input_fd = open(filename, O_RDONLY);
		}
		if (command->redirect_type & LIM_READ)
		{
			if (command->input_fd > 1)
				close(command->input_fd);
//			command->input_fd = open(filename, O_RDONLY);
			command->input_fd = open_tmp_file(filename);
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


