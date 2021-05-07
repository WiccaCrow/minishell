#include "../includes/minishell.h"

void show_parse_result(t_all *all)
{
	int i;
	
	printf("command flag = %d\n", all->flag_command);
	i = 0;
	if (all->args)
	{
		while (all->args[i])
		{
			printf("arg %d:\"%s\"\n", i, all->args[i]);
			i++;
		}
	}
}

static int	is_command(const char *str, const char *command)
{
	int i;

	if (str && command)
	{
		i = 0;
		while (str[i] == command[i] && (str[i] && command[i]))
			i++;
//		++i;
		if ((str[i] == 0 || str[i] == ' ') && !command[i])
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
	all->flag_command = get_command(all);
//	args = ft_split(skip_command(all->line), ' ');
//	all->args = args;
	get_args(all);
	show_parse_result(all);
	if (all->flag_command)
	{
		free(all->line);
		all->line = NULL;
	}
	return (1);
}