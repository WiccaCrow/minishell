#include "../includes/minishell.h"

char	**get_history(void)
{
	return (ft_split("pwd ls echo", ' '));
}

int		show_prev_command(char **history)
{
	(void) history;
	return ((int)write(STDOUT_FILENO, "prev_command", 12));
}

int		show_next_command(char **history)
{
	(void) history;
	return ((int)write(STDOUT_FILENO, "next_command", 12));
}
