#include "minishell.h"

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
			if (!ft_strncmp(stop_str, curr_line, ft_strlen(curr_line)))
				break ;
			line = gnl_strjoin(line, curr_line);
			free(curr_line);
			curr_line = NULL;
		}
		write (fd, line, gnl_strlen(line));
		free(line);
		close(fd);
		fd = open(TMP_FILE, O_RDONLY, 0644);
	}
	return (fd);
}

int open_file(t_command *command, char *filename, char *pwd)
{
	char	*full_path;
	int 	input_fd;
	
	if (command && filename && pwd)
	{
		full_path = gnl_strjoin(NULL, pwd);
		full_path = gnl_strjoin(full_path, "/");
		full_path = gnl_strjoin(full_path, filename);
		if (command->redirect_type & APPEND)
		{
			if (command->output_fd > 1)
				close(command->output_fd);
			command->output_fd = open(full_path, O_CREAT | O_WRONLY |
												O_APPEND, 0644);
		}
		if (command->redirect_type & WRITE)
		{
			if (command->output_fd > 1)
				close(command->output_fd);
			command->output_fd = open(full_path, O_CREAT | O_WRONLY |
												O_TRUNC, 0644);
		}
		if (command->redirect_type & READ)
		{
			input_fd = open(full_path, O_RDONLY);
		}
		command->redirect_type = command->redirect_type & ~(NO_FILENAME);
		free(full_path);
		if (command->output_fd < 0)
		{
			executable_error_print(filename, ": No such file or directory\n",
						  1);
			return (-1);
		}
		if (input_fd < 0)
		{
			executable_error_print(filename, ": No such file or directory\n",
								   1);
			command->input_fd = input_fd;
			return (-1);
		}
		else if (command->redirect_type & READ)
			command->input_fd = input_fd;
	}
	return (0);
}


