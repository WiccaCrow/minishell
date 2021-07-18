#include "minishell.h"

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

int	get_line(t_all *all)
{
	t_line			line;
	ssize_t			ret;
	char			*termtype;
	char			buff[10];

	init_t_line(&line, all);
	termtype = getenv("TERM");
	if (!canon_off() && termtype && tgetent(0, termtype))
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
		{
			all->line = gnl_strjoin(NULL, line.main_line);
			free_t_line(&line);
			return (1);
		}
	}
	return (0);
}

/**
 * Функция записывает законченную командную строку в основную структуру
*/

int	line_getter(t_all *all)
{
	if (get_line(all))
	{
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	write(STDOUT_FILENO, "\n", 1);
	return (0);
}
