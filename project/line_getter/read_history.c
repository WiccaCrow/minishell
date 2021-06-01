#include "../includes/minishell.h"

char 		*read_history(int fd)
{
	char	*history_line;
	char	*line;
	int		ret;
	
	history_line = NULL;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		history_line = gnl_strjoin(history_line, "\n");
		history_line = gnl_strjoin(history_line, line);
		free(line);
		ret = get_next_line(fd, &line);
	}
	if (line)
	{
		history_line = gnl_strjoin(history_line, "\n");
		history_line = gnl_strjoin(history_line, line);
		free(line);
	}
	return (history_line);
	
}

