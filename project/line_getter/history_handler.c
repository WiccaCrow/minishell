#include "../includes/minishell.h"

/**
 * Функция обрабатывает нажатие клавиши вверх
 * (показывает предыдущую команду)
 * 
 * Очищаем набранные символы в строке,
 * позицию курсора ставим в ноль
 * уменьшаем номер строки в истории
 * выводим команду из истории
 * очищаем текущую строку
 * возвращаем копию команды из истории
*/

int	show_prev_command(char **history, t_line *line)
{
	if (!(line->tmp_line) && !history[line->hist_pos])
	{
		line->tmp_line = gnl_strjoin(NULL, line->curr_line);
	}
	while (line->pos && !tputs(cursor_left, 1, ft_putchar) && \
					!tputs(tgetstr("ce", 0), 1, ft_putchar))
		line->pos--;
	if (line->hist_pos > 0)
		line->hist_pos--;
	line->pos += write(STDOUT_FILENO, history[line->hist_pos], \
		gnl_strlen(history[line->hist_pos]));
	free(line->curr_line);
	line->curr_line = gnl_strjoin(NULL, history[line->hist_pos]);
	if (line->curr_line)
		return (1);
	return (0);
}

/**
 * Функция обрабатывает нажатие клавиши вниз
 * (показывает следующую команду)
 * 
 * Очищаем набранные символы в строке,
 * позицию курсора ставим в ноль
 * увеличиваем номер строки в истории
 * выводим команду из истории
 * очищаем текущую строку
 * возвращаем копию команды из истории
*/

static int	put_tmp_line(t_line *line)
{
	line->hist_pos = line->hist_len;
	line->pos += write(STDOUT_FILENO, line->tmp_line, \
			ft_strlen(line->tmp_line));
	free(line->curr_line);
	line->curr_line = gnl_strjoin(NULL, line->tmp_line);
	return (1);
}

int	show_next_command(char **history, t_line *line)
{
	if (!(line->tmp_line) && !history[line->hist_pos])
		line->tmp_line = gnl_strjoin(NULL, line->curr_line);
	while (line->pos && !tputs(cursor_left, 1, ft_putchar) && \
					!tputs(tgetstr("ce", 0), 1, ft_putchar))
		line->pos--;
	if (line->hist_pos < line->hist_len - 1)
	{
		line->hist_pos++;
		line->pos += write(STDOUT_FILENO, history[line->hist_pos], \
			ft_strlen(history[line->hist_pos]));
		free(line->curr_line);
		line->curr_line = gnl_strjoin(NULL, history[line->hist_pos]);
		return (1);
	}
	else if (line->tmp_line)
		return (put_tmp_line(line));
	else
	{
		free(line->curr_line);
		line->curr_line = NULL;
	}
	return (0);
}

/**
 * Функция добавляет строку к истории
 * 
 * Вся история собирается в одну строку
 * к этой строке добавляем еще одну поданную на вход
 * чистим старую историю
 * в адрес истории сплитим полученную суммарную строку
*/

int	add_to_history(char *line, char ***history)
{
	int		i;
	char	*history_line;

	i = 0;
	if (line && history && *history)
	{
		history_line = NULL;
		while ((*history)[i])
		{
			if (history_line)
				history_line = gnl_strjoin(history_line, "\n");
			history_line = gnl_strjoin(history_line, (*history)[i]);
			i++;
		}
		if (history_line)
			history_line = gnl_strjoin(history_line, "\n");
		history_line = gnl_strjoin(history_line, line);
		if (history_line && free_char_array(*history))
		{
			*history = ft_split(history_line, '\n');
			ft_free((void **)&history_line);
			return (1);
		}
		return (0);
	}
	return (1);
}

/**
 * Функция считает длину массива(истории)
*/

int	history_len(char **history)
{
	int	len;

	len = 0;
	if (history)
		while (history[len])
			len++;
	return (len);
}
