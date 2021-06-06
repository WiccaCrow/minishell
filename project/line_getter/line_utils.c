#include "../includes/minishell.h"

/**
 * Функция добавления символа в строку
 * 
 * Добавляет символ в указанную позицию в строку, остаток строки сдвигается 
 * на 1 символ, позиция курсора также сдвигается на 1 позицию вправо
*/

int 		add_chr_to_pos(t_line *line, char c)
{
	char	*new_str;
	size_t	size;
	size_t	i;

	size = gnl_strlen(line->curr_line) + 2;
	new_str = (char *)malloc(sizeof(char) * size);
	if (new_str)
	{
		if (c == '\n')
			line->pos = ft_strlen(line->curr_line);
		i = 0;
		while (line->curr_line && line->curr_line[i] && i < line->pos)
		{
			new_str[i] = line->curr_line[i];
			i++;
		}
		new_str[i++] = c;
		while (line->curr_line && line->curr_line[i - 1])
		{
			new_str[i] = line->curr_line[i - 1];
			i++;
		}
		new_str[i] = 0;
		free(line->curr_line);
		line->curr_line = new_str;
		size = write(STDIN_FILENO, &new_str[line->pos], ft_strlen(&new_str[line->pos]))
				- 1;
		while (size--)
			tputs(cursor_left, 1, ft_putchar);
		line->pos++;
		line->hist_pos = line->hist_len;
		free(line->tmp_line);
		line->tmp_line = NULL;
		return (1);
	}
	return (0);
}

/**
 * Функция удаления символа из строки
 * 
 * Удаляет символ из указанной позицию в строке, остаток строки сдвигается 
 * на 1 символ, позиция курсора также сдвигается на 1 позицию влево
*/

int			remove_chr_from_pos(t_line *line)
{
	char	*new_str;
	size_t	size;
	size_t 	i;

	if (line->pos)
	{
		tputs(cursor_left, 1, ft_putchar);
		tputs(delete_character, 1, ft_putchar);
		size = gnl_strlen(line->curr_line);
		new_str = (char *) malloc(sizeof(char) * size);
		if (new_str)
		{
			i = 0;
			while (line->curr_line && line->curr_line[i] && i < (line->pos - 1))
			{
				new_str[i] = line->curr_line[i];
				i++;
			}
			i++;
			while (line->curr_line && line->curr_line[i - 1])
			{
				new_str[i - 1] = line->curr_line[i];
				i++;
			}
			new_str[i - 1] = 0;
			free(line->curr_line);
			line->curr_line = new_str;
			line->pos--;
			line->hist_pos = line->hist_len;
			free(line->tmp_line);
			line->tmp_line = NULL;
			return (1);
		}
	}
	return (0);
}


