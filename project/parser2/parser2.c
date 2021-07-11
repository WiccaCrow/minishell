#include "minishell.h"

/**
 * Первый элемент из листа комманд пишет в старую структуру, где есть место 
 * только для одной комманды
*/

int show_commands(t_command **commands)
{
	t_command *tmp;
	int i;
	
	if (commands)
	{
		tmp = *commands;
		while (tmp)
		{
			write(STDOUT_FILENO, CURSIVE, 8);
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
			write(STDOUT_FILENO, NONECOLOR, 4);
			tmp = tmp->next;
		}
	}
	return (0);
}

static int	get_next_word(char *line, int i, char **tmp_line)
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
				return (HEREDOC);
		if (word[0] == '<' && word[1] == '<' && word[2] == 0)
				return (HEREDOC | NO_FILENAME);
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

int parse_redirect(t_command *command, char *word, char *pwd)
{
	char *filename;
	
	if (!(command->redirect_type & NO_FILENAME))
	{
		filename = get_filename(word);
		if (filename)
		{
			open_file(command, filename, pwd);
			return (1);
		}
	}
	return (0);
}

int parse_word(char *word, t_command *command, t_list **args, char *pwd)
{
	if (command->redirect_type && (command->redirect_type & NO_FILENAME))
	{
		if (open_file(command, word, pwd) < 0)
			return (0);
	}
	else
	{
		command->redirect_type = set_redirect(word);
		if (command->redirect_type)
		{
			if (parse_redirect(command, word, pwd))
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
		command->input_fd = heredoc_handle(all, i);
		command->output_fd = 1;
		args = (t_list **)ft_calloc(1, sizeof(t_list *));
		if (args)
		{
			while (all->line[i] && all->line[i] != ';' && all->line[i] != '|')
			{
				curr_line = NULL;
				i = get_next_word(all->line, i, &curr_line);
				i = skip_spaces(all->line, i);
				if ((parse_word(curr_line, command, args, all->pwd) < 0))
					all->parse_error = 1;
				free(curr_line);
				curr_line = NULL;
			}
			if (*args)
				command->flag_command = get_command2((char *)(*args)->content);
			if ((command->flag_command == not_found && !*args) || 
				command->redirect_type & NO_FILENAME)
				
			{
				all->parse_error = 1;
				if (command->redirect_type & NO_FILENAME)
					write(STDOUT_FILENO, SYN_ERR "newline\'\n", 56);
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
	all->parse_error = 0;
	all->commands = (t_command **)ft_calloc(1, sizeof (t_command *));
	if (all->commands)
	{
		i = skip_spaces(all->line, i);
		while (all->line && all->line[i] && all->line[i] != ';')
		{
			i = get_next_command(all, i);
			i = skip_spaces(all->line, i);
		}
		set_start_pipes(all);
		show_commands(all->commands);
		crop_line(&(all->line));
		if (all->parse_error == 0)
			return (1);
	}
	return (0);
}