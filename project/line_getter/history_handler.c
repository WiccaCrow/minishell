#include "../includes/minishell.h"

char	**get_history(void)
{
	int		fd;
	char	*history_line;

	fd = open(HIST_FILE, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd > 0)
	{
		history_line = read_history(fd);
		if (history_line)
			return (ft_split(history_line, '\n'));
		close(fd);
		
	}
	else
		write(STDOUT_FILENO, "Create/open file error\n", 23);
	return (0);
}

char 		*show_prev_command(char **history, size_t *pos, char *line)
{
	(void) history;
	while (*pos && !tputs(cursor_left, 1, ft_putchar) && \
					!tputs(tgetstr("ce", 0), 1, ft_putchar))
		(*pos)--;
	*pos += write(STDOUT_FILENO, "prev_command", 12);
	free(line);
	return (ft_strdup("prev_command"));
}

char		*show_next_command(char **history, size_t *pos, char *line)
{
	(void) history;
	while (*pos && !tputs(cursor_left, 1, ft_putchar) && \
					!tputs(tgetstr("ce", 0), 1, ft_putchar))
		(*pos)--;
	*pos += write(STDOUT_FILENO, "next_command", 12);
	free(line);
	return (ft_strdup("next_command"));
}
