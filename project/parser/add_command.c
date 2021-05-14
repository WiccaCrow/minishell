#include "../includes/minishell.h"

int	add_command(t_all *all, t_command *command)
{
	t_command *tmp;
	
	if (all && all->commands && command)
	{
		if (!(*all->commands))
		{
			*all->commands = command;
			return (0);
		}
		tmp = *all->commands;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = command;
	}
	return(0);
}