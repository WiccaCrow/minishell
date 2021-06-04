#include "../includes/minishell.h"

/**
 * Функция добавления символа в строку
 * 
 * Добавляет символ в указанную позицию в строку, остаток строки сдвигается 
 * на 1 символ, позиция курсора также сдвигается на 1 позицию вправо
*/

char	 	*add_chr_to_pos(char *str, char c, size_t *pos)
{
	char	*new_str;
	size_t	size;
	size_t	i;

	size = gnl_strlen(str) + 2;
	new_str = (char *)malloc(sizeof(char) * size);
	if (new_str)
	{
		if (c == '\n')
			*pos = ft_strlen(str);
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
		free(str);
		size = write(STDIN_FILENO, &new_str[*pos], ft_strlen(&new_str[*pos]))
				- 1;
		while (size--)
			tputs(cursor_left, 1, ft_putchar);
		(*pos)++;
	}
	return (new_str);
}

/**
 * Функция удаления символа из строки
 * 
 * Удаляет символ из указанной позицию в строке, остаток строки сдвигается 
 * на 1 символ, позиция курсора также сдвигается на 1 позицию влево
*/

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
		while (str && str[i] && i < (*pos - 1))
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


