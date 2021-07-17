#include "../includes/minishell.h"

/**
 * Функция получения законченной командной строки от пользователя
 * 
 * Переводим терминал в неканонический режим, читаем по 1 символу, 
 * обрабатываем специальные клавиши, далее возвращаем терминал в канонический
 * режим
*/

int	init_t_line(t_line *line, t_all *all)
{
	if (line)
	{
		line->main_line = NULL;
		line->curr_line = NULL;
		line->tmp_line = NULL;
		line->pos = 0;
		line->hist_pos = history_len(all->history);
		line->hist_len = line->hist_pos;
		return (1);
	}
	return (0);
}

static int	simple_char_handle(const char *buff, t_line *line, t_all *all)
{
	if (sigint_switcher(line))
		init_t_line(line, all);
	add_chr_to_pos(line, *buff);
	return (0);
}

static int	char_handle(char *buff, t_line *line, t_all *all)
{
	if (!strcmp(buff, KEY_UP))
		show_prev_command(all->history, line);
	else if (!strcmp(buff, KEY_DOWN))
		show_next_command(all->history, line);
	else if (!strcmp(buff, KEY_BACKSPACE))
		remove_chr_from_pos(line);
	else if (!strcmp(buff, KEY_RIGHT))
		key_right_handle(line);
	else if (!strcmp(buff, KEY_LEFT))
		key_left_handle(line);
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

char	*get_line(t_all *all)
{
	t_line			line;
	ssize_t			ret;
	char			*termtype;
	char			buff[10];

	init_t_line(&line, all);
	termtype = getenv("TERM");
	if (!canon_off() && termtype && tgetent(0, termtype) && \
		!tputs(save_cursor, 1, ft_putchar))
	{
		show_program_name();
		while (1)
		{
			ret = read(1, buff, 10);
			buff[ret] = 0;
			if (!char_handle(buff, &line, all))
				break ;
		}
		if (!canon_on())
			return (line.main_line);
	}
	return (NULL);
}

/**
 * Функция записывает законченную командную строку в основную структуру
*/

int	line_getter(t_all *all)
{
	all->line = get_line(all);
	if (all->line)
	{
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
//	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
