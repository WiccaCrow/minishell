#include "../includes/minishell.h"

int 		ft_putchar(int c)
{
	return (int)(write(STDOUT_FILENO, &c, 1));
}

static int	check_end_of_input(const char *line)
{
	int i;
	int flag;
	
	flag = 0;
	if (line)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '\\' && !(flag & QUOTE))
				flag = flag | SHIELD;
			if (line[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
				flag = flag ^ DOUBLE_QUOTE;
			if (line[i] == '\'' && !(flag & SHIELD) && !(flag & DOUBLE_QUOTE))
				flag = flag ^ QUOTE;
			if (line[i] != '\\' && (flag & SHIELD) && line[i + 1])
				flag = flag & ~(SHIELD);
			i++;
		}
	}
	return (flag);
}

int 	key_right_handle(char *line, size_t *pos)
{
	if (*pos < ft_strlen(line))
	{
		(*pos)++;
		tputs(cursor_right, 1, ft_putchar);
	}
	return (0);
}

int 	key_left_handle(size_t *pos)
{
	if (*pos > 0)
	{
		(*pos)--;
		tputs(cursor_left, 1, ft_putchar);
	}
	return (0);
}

char	*get_line(char **history)
{
	char			*line;
	size_t			pos;
	ssize_t			ret;
	char			*termtype;
	char			buff[10];

	line = NULL;
	termtype = getenv("TERM");
	if (!canon_off() && termtype && tgetent(0, termtype) && \
		!tputs(save_cursor, 1, ft_putchar))
	{
		pos = 0;
		while (1)
		{
			ret = read(STDIN_FILENO, buff, 10);
			buff[ret] = 0;
			if (!strcmp(buff, KEY_UP))
				line = show_prev_command(history, &pos, line);
			else if (!strcmp(buff, KEY_DOWN))
				line = show_next_command(history, &pos, line);
			else if (!strcmp(buff, KEY_BACKSPACE) && pos > 0)
				line = remove_chr_from_pos(line, &pos);
			else if (!strcmp(buff, KEY_RIGHT))
				key_right_handle(line, &pos);
			else if (!strcmp(buff, KEY_LEFT))
				key_left_handle(&pos);
			else if (!strcmp(buff, "\4") || (!strcmp(buff, "\n") &&
					!check_end_of_input(line)))
				break;
			else
				line = add_chr_to_pos(line, *buff, &pos);
		}
		if (!canon_on())
			return (line);
	}
	return (NULL);
}

int	line_getter(t_all *all)
{
	char	*line;
	char 	**history;
	
	line = NULL;
	show_program_name();
	history = get_history();
	if (history)
		line = get_line(history);
	if (line)
	{
		all->line = line;
		return (1);
	}
	return(0);
}
