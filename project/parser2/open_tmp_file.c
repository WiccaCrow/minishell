#include "minishell.h"

static int	get_line(char **line, char *stop_str)
{
	char	*curr_line;
	int		ret;

	curr_line = NULL;
	ret = 1;
	while (ret > 0)
	{
		write(STDOUT_FILENO, "> ", 2);
		ret = get_next_line(STDIN_FILENO, &curr_line);
		if (*line)
			*line = gnl_strjoin(*line, "\n");
		if (!ft_strncmp(stop_str, curr_line, ft_strlen(curr_line)))
			break ;
		*line = gnl_strjoin(*line, curr_line);
		free(curr_line);
		curr_line = NULL;
	}
	return (0);
}

int	open_tmp_file(char *stop_str)
{
	int		fd;
	char	*line;

	fd = open(TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd > 0)
	{
		line = NULL;
		get_line(&line, stop_str);
		write (fd, line, gnl_strlen(line));
		free(line);
		close(fd);
		fd = open(TMP_FILE, O_RDONLY, 0644);
	}
	return (fd);
}
