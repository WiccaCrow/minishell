#include "../includes/parser.h"

int		get_another_line(char **line)
{
	int ret;

	free(*line);
	*line = NULL;
	write(STDOUT_FILENO, "> ", 2);
	ret = get_next_line(STDIN_FILENO, line);
	if (ret != -1)
		return (1);
	return (0);
}
