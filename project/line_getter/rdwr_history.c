#include "../includes/minishell.h"

/**
 * Функция загружает историю из файла
 * 
 * Открываем файл в режиме чтения, читаем в строку файл, делим по переносу 
 * строки, чистим строку, возвращаем результат деления
*/

char	**get_history(void)
{
	int		fd;
	char	*history_line;
	char	**history;

	fd = open(HIST_FILE, O_CREAT | O_RDWR, 0644);
	if (fd > 0)
	{
		history_line = read_history(fd);
		if (history_line)
		{
			history = ft_split(history_line, '\n');
			if (history)
			{
				free(history_line);
				return (history);
			}
		}
		close(fd);
	}
	else
		write(STDOUT_FILENO, "Create/open file error\n", 23);
	return (0);
}

/**
 * Функция читает файл в строку 
*/

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

/**
 * Функция очищает двумерный массив(историю)
 * 
 * Добавляет символ в указанную позицию в строку, остаток строки сдвигается 
 * на 1 символ, позоция курсора также сдвигается на 1 позицию вправо
*/

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

/**
 * Функция пишет истоию в файл
*/

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
			ret += (int)write(fd, history[i], ft_strlen(history[i]));
			ret += (int)write(fd, "\n", 1);
		}
		close(fd);
		clean_history(history);
	}
	else
		write(STDOUT_FILENO, "Create/open file error\n", 23);
	return (ret);
}