#include "../includes/minishell.h"

static int	is_command(const char *str, const char *command)
{
	int i;

	if (str && command)
	{
		i = 0;
		while (str[i] == command[i] && (str[i] && command[i]))
			i++;
//		++i;
		if (str[i] == 0 || str[i] == ' ')
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

int parser(t_all *all)
{
	char	**strings;

	all->flag_command = get_command(all);
	strings = ft_split(all->line, ' ');
	if (strings)
	{
		all->args = &strings[1];
		return (0);
	}
	return (1);
}