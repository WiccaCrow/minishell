#include "minishell.h"

int check_line(t_all *all)
{
	int i;
	
	if (all && all->line)
	{
		if (!*all->line)
			return (0);
		i = 0;
		while (all->line[i])
		{
			if (all->line[i] == ';')
			{
				i++;
				if (all->line[i] == ';')
				{
					write(STDOUT_FILENO, SYN_ERR, 47);
					write(STDOUT_FILENO, ";;\'\n", 4);
					return (0);
				} else
				{
					i = skip_spaces(all->line, i);
					if (all->line[i] == ';' || i == 1)
					{
						write(STDOUT_FILENO, SYN_ERR, 47);
						write(STDOUT_FILENO, ";\'\n", 3);
						return (0);
					}
				}
			} else if (all->line[i] == '|')
			{
				i++;
				if (all->line[i] == '|')
				{
					write(STDOUT_FILENO, SYN_ERR, 47);
					write(STDOUT_FILENO, "||\'\n", 4);
					return (0);
				} else
				{
					i = skip_spaces(all->line, i);
					if (all->line[i] == '|' || i == 1)
					{
						write(STDOUT_FILENO, SYN_ERR, 47);
						write(STDOUT_FILENO, "|\'\n", 3);
						return (0);
					}
				}
			} else
				i++;			
		}
	}
	return (1);
}