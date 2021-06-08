#include "minishell.h"

/**
 * Функция показывает результат парсинга
*/

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

/**
 * Функция получает из строки команду с параметрами
*/

int parse_command(t_all *all, int i)
{
	t_command	*command;
	t_list		**list;
	
	command = (t_command *)malloc(sizeof (t_command));
	if (command)
	{
		command->redirect_type = 0;
		command->input_fd = STDIN_FILENO;
		command->output_fd = STDOUT_FILENO;
		list = NULL;
		i = get_list(all, i, &list);
		parse_list(command, list);
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

/**
 * Первый элемент из листа комманд пишет в старую структуру, где есть место 
 * только для одной комманды
*/

int set_command_to_all(t_all *all)
{
	all->flag_command = (*all->commands)->flag_command;
	all->args = (*all->commands)->args;
	return (0);
}

/**
 * Основная функция парсинга строки
 * 
 * Идем по строке, находим комманды и их аргументы, все собираем в лист
*/

int parser(t_all *all)
{
	int			i;
	
	i = 0;
	all->commands = (t_command **)malloc(sizeof (t_command *));
	if (all->commands)
	{
		*all->commands = NULL;
		i = skip_spaces(all->line, i);
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