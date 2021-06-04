#include "../includes/minishell.h"

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

int		add_to_history(char *line, char ***history)
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