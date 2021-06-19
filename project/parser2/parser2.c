#include "minishell.h"

/**
 * Первый элемент из листа комманд пишет в старую структуру, где есть место 
 * только для одной комманды
*/

int set_command_to_all(t_all *all)
{
	if (all->commands && *all->commands)
	{
		all->flag_command = (*all->commands)->flag_command;
		all->args = (*all->commands)->args;
	}
	else
		all->flag_command = not_found;
	return (0);
}

int show_commands(t_command **commands)
{
	t_command *tmp;
	int i;
	
	if (commands)
	{
		tmp = *commands;
		while (tmp)
		{
			printf("command flag = %d\n", tmp->flag_command);
			printf("redirect flag = %d\n", tmp->redirect_type);
			printf("input fd = %d\n", tmp->input_fd);
			printf("output fd = %d\n", tmp->output_fd);
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
	return (0);
}

int get_next_word(char *line, int i, char **tmp_line)
{
	int	flag;

	flag = 0;
	while (line[i])
	{
		if (line[i] == '\\' && !(flag & QUOTE) && !(flag & SHIELD))
		{
			flag = flag | SHIELD;
			i++;
		}
		else if (line[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
		{
			flag = flag ^ DOUBLE_QUOTE;
			i++;
		}
		else if (line[i] == '\'' && !(flag & SHIELD) && !(flag & DOUBLE_QUOTE))
		{
			flag = flag ^ QUOTE;
			i++;
		}
		else if ((line[i] != ' ' && line[i] != ';' && line[i] != '|') || flag)
		{
			*tmp_line = add_chr(*tmp_line, line[i++]);
			if (line[i])
				flag = flag & ~(SHIELD);
		}
		else
			return (i);
	}
	return (i);
}

int 	set_redirect(const char *word)
{
	if (word)
	{
		if (word[0] == '>' && word[1] == '>' && word[2] != 0)
				return (APPEND);
		if (word[0] == '>' && word[1] == '>' && word[2] == 0)
				return (APPEND | NO_FILENAME);
		if (word[0] == '<' && word[1] == '<' && word[2] != 0)
				return (LIM_READ);
		if (word[0] == '<' && word[1] == '<' && word[2] == 0)
				return (LIM_READ | NO_FILENAME);
		if (word[0] == '>' && word[1] != 0)
				return (WRITE);
		if (word[0] == '>' && word[1] == 0)
				return (WRITE | NO_FILENAME);
		if (word[0] == '<' && word[1] != 0)
				return (READ);
		if (word[0] == '<' && word[1] == 0)
				return (READ | NO_FILENAME);
	}
	return (0);
}

char *get_filename(char *word)
{
	if (word)
	{
		if ((word[0] == '>' && word[1] == '>') || \
			(word[0] == '<' && word[1] == '<'))
			return (ft_strdup(word + 2));
		if (word[0] == '>' || word[0] == '<')
			return (ft_strdup(word + 1));
	}
	return (NULL);
}

int parse_redirect(t_command *command, char *word)
{
	char *filename;
	
	if (!(command->redirect_type & NO_FILENAME))
	{
		filename = get_filename(word);
		if (filename)
		{
			open_file(command, filename);
			return (1);
		}
	}
	return (0);
}

int parse_word(char *word, t_command *command, t_list **args)
{
	if (command->redirect_type && (command->redirect_type & NO_FILENAME))
	{
		if (open_file(command, word) < 0)
			return (-1);
	}
	else
	{
		command->redirect_type = set_redirect(word);
		if (command->redirect_type)
		{
			if (parse_redirect(command, word))
				return (1);
			else
				return (2);
		}
		else
			ft_lstadd_back(args, ft_lstnew(ft_strdup(word)));
	}
	return (0);
}

int get_next_command(t_all *all, int i)
{
	t_command	*command;
	char 		*curr_line;
	t_list		**args;

	command = (t_command *)ft_calloc(1, sizeof (t_command));
	if (command)
	{
		args = (t_list **) ft_calloc(1, sizeof(t_list *));
		if (args)
		{
			command->output_fd = 1;
			while (all->line[i] && all->line[i] != ';' && all->line[i] != '|')
			{
				curr_line = NULL;
				i = get_next_word(all->line, i, &curr_line);
				i = skip_spaces(all->line, i);
				if ((parse_word(curr_line, command, args) < 0))
					all->parse_error = 1;
				free(curr_line);
				curr_line = NULL;
			}
			if (*args)
				command->flag_command = get_command2((char *)(*args)->content);
			else if (command->flag_command == not_found || 
			command->redirect_type & NO_FILENAME)
			{
				all->parse_error = 1;
				if (command->redirect_type & NO_FILENAME)
				{
					write(STDOUT_FILENO, SYN_ERR, 47);
					write(STDOUT_FILENO, "newline\'\n", 9);
				}
			}
			if (command->flag_command)
				remove_first(args);
			args_list_to_arr2(args, command);
			clear_list2(args);
			if (all->line[i] == ';')
				command->end_flag = SEMICOLON;
			else if (all->line[i] == '|')
			{
				command->end_flag = PIPE;
				i++;
			} else
				command->end_flag = 0;
			command->next = NULL;
			add_command(all, command);
		}
	}
	return (i);
}

int parser2(t_all *all)
{
	int			i;

	i = 0;
	all->commands = (t_command **)malloc(sizeof (t_command *));
	all->parse_error = 0;
	if (all->commands)
	{
		*all->commands = NULL;
		i = skip_spaces(all->line, i);
		while (all->line && all->line[i] && all->line[i] != ';')
		{
			i = get_next_command(all, i);
			i = skip_spaces(all->line, i);
		}
		show_commands(all->commands);
		set_command_to_all(all);
		crop_line(&(all->line));
		if (all->parse_error == 0)
			return (1);
	}
	return (0);
}