#include "../includes/minishell.h"

char *get_line(void)
{
	return ("test");
}

int	line_getter(t_all *all)
{
	char	*line;
	
	line = NULL;
	
	show_program_name();
	line = get_line();
	if (line)
	{
		all->line = line;
		return (1);
	}
	return(0);
}
