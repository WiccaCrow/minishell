#include "../includes/minishell.h"

int 		ft_putchar(int c)
{
	return (int)(write(STDOUT_FILENO, &c, 1));
}

char	*get_line(t_all *all)
{
	char			*line;
	char			*curr_line;
	int 			hist_pos;
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
		hist_pos = history_len(all->history);
		while (1)
		{
			ret = read(STDIN_FILENO, buff, 10);
			buff[ret] = 0;
			if (!strcmp(buff, KEY_UP))
				curr_line = show_prev_command(all->history, &pos, line, &hist_pos);
			else if (!strcmp(buff, KEY_DOWN))
				curr_line = show_next_command(all->history, &pos, line, &hist_pos);
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
				if (enter_handle(&line, &curr_line, &pos) && add_to_history
				(line, &(all->history)))
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
	
	line = NULL;
	line = get_line(all);
	if (line)
	{
		all->line = line;
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	return(0);
}
