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

int parser(t_all *all)
{
//	all->commands = (t_command **)malloc(sizeof (t_command *));
//	if (all->commands)
//	{
//		*(all->commands) = NULL;
//		while (add_command(all))
//			;
		all->flag_command = get_command(all);
		get_args(all);
		show_parse_result(all);
		if (all->flag_command)
			crop_line(&(all->line));
//		if (all->line)
//			return (1);
//	}
	return (1);
}