#include "../includes/minishell.h"

static int	is_command(const char *str, const char *command)
{
	int i;

	if (str && command)
	{
		i = 0;
		while (str[i] == command[i] && (str[i] && command[i]))
			i++;
		if ((str[i] == 0 || str[i] == ' ' || str[i] == ';') && !command[i])
			return (1);
	}
	return (0);
}


enum e_command	get_command(t_all *all)
{
	int	i;

	i = 0;
	while (++i <= 10)
		if (all->line && is_command(all->line, all->all_commands[i - 1]))
			return i;
	return (0);
}