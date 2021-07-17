#include "minishell.h"

int	set_redirect(const char *word)
{
	int	i;

	if (word)
	{
		i = 0;
		while (ft_isdigit(word[i]))
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

int	command_check(t_command *command, t_all *all, t_list **args)
{
	if (*args)
		command->flag_command = get_command((char *)(*args)->content);
	if ((command->flag_command == not_found && !*args) || \
				command->redirect_type & NO_FILENAME)
	{
		all->parse_error = 1;
		if (command->redirect_type & NO_FILENAME)
			write(STDOUT_FILENO, SYN_ERR "newline\'\n", 56);
	}
	if (command->flag_command)
		remove_first(args);
	return (0);
}

int	set_command_end(t_command *command, t_all *all, int i)
{
	if (all->line[i] == ';')
		command->end_flag = SEMICOLON;
	else if (all->line[i] == '|')
	{
		command->end_flag = PIPE;
		i++;
	}
	else
		command->end_flag = 0;
	return (i);
}

int	get_next_command(t_all *all, int i)
{
	t_command	*command;
	t_list		**args;

	command = (t_command *)ft_calloc(1, sizeof (t_command));
	if (command)
	{
		command->input_fd = heredoc_handle(all, i);
		command->output_fd = 1;
		args = (t_list **)ft_calloc(1, sizeof(t_list *));
		if (args)
		{
			i = fill_args(all, i, command, args);
			command_check(command, all, args);
			args_list_to_arr2(args, command);
			clear_list2(args);
			i = set_command_end(command, all, i);
			command->next = NULL;
			add_command(all, command);
		}
	}
	return (i);
}

int	parser2(t_all *all)
{
	int	i;

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
		crop_line(&(all->line));
		if (all->parse_error == 0 && *(all->commands))
			return (1);
	}
	return (0);
}
