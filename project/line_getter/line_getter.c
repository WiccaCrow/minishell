#include "../includes/minishell.h"

int 		ft_putchar(int c)
{
	return (int)(write(STDOUT_FILENO, &c, 1));
}

char	 	*add_chr_to_pos(char *str, char c, size_t *pos)
{
	char	*new_str;
	size_t	size;
	size_t	i;

	size = gnl_strlen(str) + 2;
	new_str = (char *)malloc(sizeof(char) * size);
	if (new_str)
	{
		i = 0;
		while (str && str[i] && i < *pos)
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i++] = c;
		while (str && str[i - 1])
		{
			new_str[i] = str[i - 1];
			i++;
		}
		new_str[i] = 0;
	}
	free(str);
	size = write(STDIN_FILENO, &new_str[*pos], ft_strlen(&new_str[*pos])) - 1;
	while (size--)
		tputs(cursor_left, 1, ft_putchar);
	(*pos)++;
	return (new_str);
}

char	 	*remove_chr_from_pos(char *str, size_t *pos)
{
	char	*new_str;
	size_t	size;
	size_t 	i;

	tputs(cursor_left, 1, ft_putchar);
	tputs(delete_character, 1, ft_putchar);
	size = gnl_strlen(str);
	new_str = (char *)malloc(sizeof(char) * size);
	if (new_str)
	{
		i = 0;
		while (str && str[i] && i < *pos)
		{
			new_str[i] = str[i];
			i++;
		}
		i++;
		while (str && str[i - 1])
		{
			new_str[i - 1] = str[i];
			i++;
		}
		new_str[i - 1] = 0;
	}
	free(str);
	(*pos)--;
	return (new_str);
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
			else if (!strcmp(buff, "\4") || !strcmp(buff, "\n"))
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
