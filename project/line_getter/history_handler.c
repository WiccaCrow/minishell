#include "../includes/minishell.h"

char	**get_history(void)
{
	return (ft_split("pwd ls echo", ' '));
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
