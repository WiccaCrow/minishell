#include "minishell.h"

/**
 * Первый элемент из листа комманд пишет в старую структуру, где есть место 
 * только для одной комманды
*/

int 	set_redirect(const char *word)
{
	int i;

	if (word)
	{
		i = 0;
		while(ft_isdigit(word[i]))
			i++;
		if (word[i] == '>' && word[i + 1] == '>' && word[i + 2] != 0)
			return (APPEND);
		if (word[i] == '>' && word[i + 1] == '>' && word[i + 2] == 0)
			return (APPEND | NO_FILENAME);
		if (word[i] == '<' && word[i + 1] == '<' && word[i + 2] != 0)
			return (HEREDOC);
		if (word[i] == '<' && word[i + 1] == '<' && word[i + 2] == 0)
			return (HEREDOC | NO_FILENAME);
		if (word[i] == '>' && word[i + 1] != 0)
			return (WRITE);
		if (word[i] == '>' && word[i + 1] == 0)
			return (WRITE | NO_FILENAME);
		if (word[i] == '<' && word[i + 1] != 0)
			return (READ);
		if (word[i] == '<' && word[i + 1] == 0)
			return (READ | NO_FILENAME);
	}
	return (0);
}

char	*get_filename(char *word)
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

int	parse_redirect(t_command *command, char *word, char *pwd)
{
	char	*filename;

	
	if (!(command->redirect_type & NO_FILENAME))
	{
		filename = get_filename(word);
		if (filename)
		{
			open_file(command, filename, pwd);
			return (1);
		}
	}
	return (handle_pre_fd(command, word));
}

int	parse_word(char *word, t_command *command, t_list **args, char *pwd)
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
				return (-1);
		}
		else
			ft_lstadd_back(args, ft_lstnew(ft_strdup(word)));
	}
	return (0);
}

int	get_next_command(t_all *all, int i)
{
	t_command	*command;
	char		*curr_line;
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
				i = get_next_word_lc(all->line, i, &curr_line);
				i = skip_spaces(all->line, i);
				if ((parse_word(curr_line, command, args, all->pwd) < 0))
					all->parse_error = 1;
				free(curr_line);
				curr_line = NULL;
			}
			if (*args)
				command->flag_command = get_command((char *) (*args)->content);
			if ((command->flag_command == not_found && !*args) || \
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
			}
			else
				command->end_flag = 0;
			command->next = NULL;
			add_command(all, command);
		}
	}
	return (i);
}

int	parser2(t_all *all)
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
