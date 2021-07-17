#include "minishell.h"

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
		if (open_file(command, clear_word(ft_strdup(word)), pwd) < 0)
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
			ft_lstadd_back(args, ft_lstnew(clear_word(ft_strdup(word))));
	}
	return (0);
}

int	fill_args(t_all *all, int i, t_command *command, t_list **args)
{
	char	*curr_line;

	while (all->line[i] && all->line[i] != ';' && all->line[i] != '|')
	{
		curr_line = NULL;
		i = get_next_word_lc(all->line, i, &curr_line);
		i = skip_spaces(all->line, i);
		if ((parse_word(curr_line, command, args, all->pwd) < 0))
			all->parse_error = 1;
		ft_free((void **)&curr_line);
	}
	return (i);
}
