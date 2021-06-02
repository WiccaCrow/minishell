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

int		write_history(char **history)
{
	int i;
	int ret;
	int fd;

	ret = 0;
	fd = open(HIST_FILE, O_CREAT | O_RDWR | O_TRUNC | O_APPEND, 0644);
	if ((fd > 0) && (history))
	{
		i = -1;
		while (history[++i])
		{
			ret += write(fd, history[i], ft_strlen(history[i]));
			ret += write(fd, "\n", 1);
		}
		close(fd);
		clean_history(history);
	}
	return (ret);
}


int add_to_history(char *line, char ***history)
{
	int i;
	char *history_line;

	i = 0;
	if (line && history && *history)
	{
		history_line = NULL;
		while((*history)[i])
		{
			if (history_line)
				history_line = gnl_strjoin(history_line, "\n");
			history_line = gnl_strjoin(history_line, (*history)[i]);
			i++;
		}
		if (history_line)
			history_line = gnl_strjoin(history_line, "\n");
		history_line = gnl_strjoin(history_line, line);
		if (history_line && clean_history(*history))
		{
			*history = ft_split(history_line, '\n');
			return (1);
		}
	}
	return (0);
}

int	clean_history(char **history)
{
	int i;

	if (history)
	{
		i = -1;
		while (history[++i])
			free(history[i]);
		free(history);
		history = NULL;
		return (1);
	}
	return (0);
}
