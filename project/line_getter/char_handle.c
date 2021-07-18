#include "minishell.h"

static int	simple_char_handle(const char *buff, t_line *line, t_all *all)
{
	int	i;

	if (sigint_switcher(line))
		init_t_line(line, all);
	if (*buff != 9)
		add_chr_to_pos(line, *buff);
	else
	{
		i = -1;
		while (++i < 4)
			add_chr_to_pos(line, ' ');
	}
	return (1);
}

int	simple_keys_handle(char *buff, t_line *line)
{
	if (!strcmp(buff, KEY_BACKSPACE))
	{
		remove_chr_from_pos(line);
		return (1);
	}
	else if (!strcmp(buff, KEY_RIGHT))
	{
		key_right_handle(line);
		return (1);
	}
	else if (!strcmp(buff, KEY_LEFT))
	{
		key_left_handle(line);
		return (1);
	}
	return (0);
}

int	char_handle(char *buff, t_line *line, t_all *all)
{
	if (sigint_switcher(line))
		init_t_line(line, all);
	if (!strcmp(buff, KEY_UP))
		show_prev_command(all->history, line);
	else if (!strcmp(buff, KEY_DOWN))
		show_next_command(all->history, line);
	else if (simple_keys_handle(buff, line))
		(void) line;
	else if (!strcmp(buff, "\4"))
	{
		if (control_d_handle(line) && line->main_line)
			return (0);
	}
	else if (!strcmp(buff, "\n"))
	{
		if (enter_handle(line) && \
			add_to_history(line->main_line, &(all->history)))
			return (0);
	}
	else
		simple_char_handle(buff, line, all);
	return (1);
}
