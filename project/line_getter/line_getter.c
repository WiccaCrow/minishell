#include "../includes/minishell.h"

int 		ft_putchar(int c)
{
	return (int)(write(STDOUT_FILENO, &c, 1));
}

char	*get_line(char **history)
{
	char			*line;
	char			*curr_line;
	size_t			pos;
	ssize_t			ret;
	char			*termtype;
	char			buff[10];

	line = NULL;
	curr_line = NULL;
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
				curr_line = show_prev_command(history, &pos, line);
			else if (!strcmp(buff, KEY_DOWN))
				curr_line = show_next_command(history, &pos, line);
			else if (!strcmp(buff, KEY_BACKSPACE) && pos > 0)
				curr_line = remove_chr_from_pos(curr_line, &pos);
			else if (!strcmp(buff, KEY_RIGHT))
				key_right_handle(line, &pos);
			else if (!strcmp(buff, KEY_LEFT))
				key_left_handle(&pos);
			else if (!strcmp(buff, "\4"))
				break ;
			else if (!strcmp(buff, "\n"))
			{
				if (enter_handle(&line, &curr_line, &pos) && add_to_history(line, &history))
					break ;
			}
			else
				curr_line = add_chr_to_pos(curr_line, *buff, &pos);
		}
		if (!canon_on())
		{
			return (line);
		}
	}
	return (NULL);
}

int	line_getter(t_all *all)
{
	char	*line;
	char 	**history;
	// int 	i;
	
	line = NULL;
	history = get_history();
	// i = 0;
	// while (history && history[i])
	// 	printf("%s\n", history[i++]);
	//	if (history)
	line = get_line(history);
	if (line)
	{
		all->line = line;
		write(STDOUT_FILENO, "\n", 1);
		// write_history(history);
		return (1);
	}
	return(0);
}
