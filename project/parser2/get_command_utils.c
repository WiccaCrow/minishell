#include "minishell.h"

/**
 * Функция пропускает пробелы
*/

int	skip_spaces(const char *line, int i)
{
	while (line && ((line[i] >= 9 && line[i] <= 13) || line[i] == 32))
		i++;
	return (i);
}

/**
 * Функция добавляет символ в строку
*/

char	*add_chr(char *str, char c)
{
	char	*new_str;
	size_t	size;
	int		i;

	size = gnl_strlen(str) + 2;
	new_str = (char *)malloc(sizeof(char) * size);
	if (new_str)
	{
		i = 0;
		while (str && str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i++] = c;
		new_str[i] = 0;
	}
	if (str && *str)
		ft_free((void *)&str);
	return (new_str);
}
