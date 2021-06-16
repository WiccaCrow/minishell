#include "../includes/minishell.h"

/**
 * Функция проверяет достигли ли мы конца ввода
 * 
 * выставляется флаг при открытии кавычек и снимается при закрытии, для слэша
 * экранируется один символ после него
 * если по завершении строки есть открытая кавычка или слэш, ввод не окончен
*/

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
	return (!flag);
}

/**
 * Функция обрабатывает нажатие клавиши Enter
 * 
 * Если есть уже набранная строка, то добавляем к ней текущую
 * Если ввод окончен, возвращаем 1,
 * если нет, предлагаем пользователю продолжить ввод
*/

int		enter_handle(t_line *line)
{
	if (line->main_line)
		line->main_line = gnl_strjoin(line->main_line, "\n");
	line->main_line = gnl_strjoin(line->main_line, line->curr_line);
	if (line->main_line)
	{
		free(line->curr_line);
		line->curr_line = NULL;
		if (check_end_of_input(line->main_line))
			return (1);
		else
		{
			line->pos = 0;
			write(STDOUT_FILENO, "\n> ", 3);
		}
	}
	return (0);
}

/**
 * Функция обрабатывает нажатие стрелочки вправо
 * 
 * Перемещаем курсор на позицию вправо, если есть куда
*/

int 	key_right_handle(t_line *line)
{
	if (line->pos < ft_strlen(line->curr_line))
	{
		line->pos++;
		tputs(cursor_right, 1, ft_putchar);
	}
	return (0);
}

/**
 * Функция обрабатывает нажатие стрелочки влево
 * 
 * Перемещаем курсор на позицию влево, если есть куда
*/

int 	key_left_handle(t_line *line)
{
	if (line->pos > 0)
	{
		line->pos--;
		tputs(cursor_left, 1, ft_putchar);
	}
	return (0);
}

int		control_d_handle(t_line *line)
{
	if (line)
	{
		if (line->curr_line && *line->curr_line)
			return (0);
		else if (line->main_line && *line->main_line)
		{
			write(STDOUT_FILENO, UNEXP_EOF, 94);
			free(line->main_line);
			line->main_line = ft_strdup("");
			return (1);
		}
		else
		{	
			write(STDOUT_FILENO, "exit", 4);
			line->main_line = ft_strdup("exit");
		}
		return (2);
	}
	return (0);
}
