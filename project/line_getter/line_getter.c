#include "../includes/minishell.h"

int 		ft_putchar(int c)
{
	return (int)(write(STDOUT_FILENO, &c, 1));
}

char	 	*add_chr_to_pos(char *str, char c, int pos)
{
	char	*new_str;
	size_t	size;
	int 	i;

	size = gnl_strlen(str) + 2;
	new_str = (char *)malloc(sizeof(char) * size);
	if (new_str)
	{
		i = 0;
		while (str && str[i] && i < pos)
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
	return (new_str);
}

char	 	*remove_chr_from_pos(char *str, int pos)
{
	char	*new_str;
	size_t	size;
	int 	i;

	size = gnl_strlen(str);
	new_str = (char *)malloc(sizeof(char) * size);
	if (new_str)
	{
		i = 0;
		while (str && str[i] && i < pos)
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
	return (new_str);
}

char *get_line(char **history)
{
	char			*line;
	int				pos;
	int				ret;
	char			*termtype;
	char			buff[10];
	struct termios	term;

	line = NULL;
	termtype = getenv("TERM");
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, termtype);
	tputs(save_cursor, 1, ft_putchar);
	pos = 0;
	while (1)
	{
		ret = read(STDIN_FILENO, buff, 10);
		buff[ret] = 0;
		if (!strcmp(buff, KEY_UP))
		{
			while (pos)
			{
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("ce", 0), 1, ft_putchar);
				pos--;
			}
			tputs(tgetstr("ce", 0), 1, ft_putchar);
			pos += show_prev_command(history);
		}
		else if (!strcmp(buff, KEY_DOWN))
		{
			while (pos)
			{
				tputs(cursor_left, 1, ft_putchar);
				tputs(tgetstr("ce", 0), 1, ft_putchar);
				pos--;
			}
			tputs(tgetstr("ce", 0), 1, ft_putchar);
			pos += show_next_command(history);
		}
		else if (!strcmp(buff, KEY_BACKSPACE) && pos > 0)
		{
			tputs(cursor_left, 1, ft_putchar);
			tputs(delete_character, 1, ft_putchar);
			line = remove_chr_from_pos(line, pos);
			pos--;
		}
		else if (!strcmp(buff, KEY_RIGHT))
		{
			tputs(cursor_right, 1, ft_putchar);
			pos++;
		}
		else if (!strcmp(buff, KEY_LEFT))
		{
			if (pos > 0)
			{
				pos--;
				tputs(cursor_left, 1, ft_putchar);
			}
		}
		else
		{
			pos += write(STDOUT_FILENO, buff, ret);
			line = add_chr_to_pos(line, *buff, pos);
		}
		if (!strcmp(buff, "\4"))
			break;
	}
	tcgetattr(0, &term);
	term.c_lflag |= ECHO;
	term.c_lflag |= ICANON;
	tcsetattr(0, TCSANOW, &term);
	return (line);
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
