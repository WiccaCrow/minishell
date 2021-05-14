#include "../includes/minishell.h"

void show_parse_result(t_all *all)
{
	int i;
	t_command *tmp;
	
	printf("OLD command flag = %d\n", all->flag_command);
	i = 0;
	if (all->args)
	{
		while (all->args[i])
		{
			printf("OLD arg %d:\"%s\"\n", i, all->args[i]);
			i++;
		}
	}
	if (all->commands)
	{
		tmp = *all->commands;
		while (tmp)
		{
			printf("command flag = %d\n", tmp->flag_command);
			printf("end flag = %d\n", tmp->end_flag);
			i = 0;
			if (tmp->args)
			{
				while (tmp->args[i])
				{
					printf("arg %d:\"%s\"\n", i, tmp->args[i]);
					i++;
				}
			}
			tmp = tmp->next;
		}
	}
	
}

int parse_command(t_all *all, int i)
{
	t_command	*command;
	
	command = (t_command *)malloc(sizeof (t_command));
	if (command)
	{
		command->flag_command = get_command(all);
		i = get_args(all, command, i);
		if (all->line[i] == ';')
			command->end_flag = SEMICOLON;
		else if (all->line[i] == '|')
		{
			command->end_flag = PIPE;
			i++;
		}
		else
			command->end_flag = 0;
		command->next = NULL;
		add_command(all, command);
	}
	return (i);
}

int set_command_to_all(t_all *all)
{
	all->flag_command = (*all->commands)->flag_command;
	all->args = (*all->commands)->args;
	return (0);
}

int parser(t_all *all)
{
	int			i;
	
	i = 0;
	all->commands = (t_command **)malloc(sizeof (t_command *));
	if (all->commands)
	{
		*all->commands = NULL;
		while (all->line && all->line[i] && all->line[i] != ';')
		{
			i = parse_command(all, i);
			i = skip_spaces(all->line, i);
		}
		set_command_to_all(all);
		show_parse_result(all);
		if (all->flag_command)
			crop_line(&(all->line));
	}
	return (1);
}