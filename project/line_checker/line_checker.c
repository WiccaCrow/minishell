#include "minishell.h"

int check_line(t_all *all)
{
	if (all && all->line)
	{
		if (!*all->line)
			return (0);
		if (*all->line == ';')
		{
			if (all->line[1] == ';')
			{
				write(STDOUT_FILENO, SYN_ERR, 47);
				write(STDOUT_FILENO, ";;\'\n", 4);
				return (0);
			}
			else
			{
				write(STDOUT_FILENO, SYN_ERR, 47);
				write(STDOUT_FILENO, ";\'\n", 3);
				return (0);
			}
		}
		else if (*all->line == '|')
		{
			if (all->line[1] == '|')
			{
				write(STDOUT_FILENO, SYN_ERR, 47);
				write(STDOUT_FILENO, "||\'\n", 4);
				return (0);
			}
			else
			{
				write(STDOUT_FILENO, SYN_ERR, 47);
				write(STDOUT_FILENO, "|\'\n", 3);
				return (0);
			}
		}
		
	}
	return (1);
}