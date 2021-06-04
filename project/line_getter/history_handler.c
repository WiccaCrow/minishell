#include "../includes/minishell.h"

char 		*show_prev_command(char **history, size_t *pos, char *line,
							   int *hist_pos)
{
	while (*pos && !tputs(cursor_left, 1, ft_putchar) && \
					!tputs(tgetstr("ce", 0), 1, ft_putchar))
		(*pos)--;
	if (*hist_pos > 0)
		(*hist_pos)--;
	*pos += write(STDOUT_FILENO, history[*hist_pos], ft_strlen(history[*hist_pos]));
	free(line);
	return (ft_strdup(history[*hist_pos]));
}

char		*show_next_command(char **history, size_t *pos, char *line,
							   int *hist_pos)
{
	while (*pos && !tputs(cursor_left, 1, ft_putchar) && \
					!tputs(tgetstr("ce", 0), 1, ft_putchar))
		(*pos)--;
	if (*hist_pos < history_len(history) - 1)
	{
		(*hist_pos)++;
		*pos += write(STDOUT_FILENO, history[*hist_pos],
					  ft_strlen(history[*hist_pos]));
		free(line);
		return (ft_strdup(history[*hist_pos]));
	}
	else
	{
		*pos += write(STDOUT_FILENO, history[*hist_pos],
					  ft_strlen(history[*hist_pos]));
		free(line);
		return (ft_strdup(history[*hist_pos]));
	}
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

int		history_len(char **history)
{
	int len;
	
	len = 0;
	if (history)
		while (history[len])
			len++;
	return (len);
}