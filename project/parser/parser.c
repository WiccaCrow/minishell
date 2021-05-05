#include "../includes/minishell.h"

int parser(t_all *all)
{
	char	**strings;
	
	strings = ft_split(all->line, ' ');
	if (strings)
	{
		all->command.command = strings;
		return (0);
	}
	return (1);
}