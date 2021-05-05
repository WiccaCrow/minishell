#include "../includes/minishell.h"

static int	is_command(const char *str, const char *command)
{
	int i;

	if (str && command)
	{
		i = 0;
		while (str[i] && command[i])
		{
			if (str[i] != command[i])
				return (0);
			i++;
		}
		if (str[i] != 0 && str[i] != ' ')
			return (0);
		return (1);
	}
	return (0);
}


enum e_command	get_command(char *line)
{
	if (is_command(line, ECHO))
		return echo;
}

int parser(t_all *all)
{
	char	**strings;
	
	all->flag_command = get_command(all->line);
	strings = ft_split(all->line, ' ');
	if (strings)
	{
		all->command.command = strings;
		return (0);
	}
	return (1);
}