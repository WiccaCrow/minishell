#include "../includes/minishell.h"

/**
 * Функция пропускает команду перед аргусментами
*/

int skip_command(const char *line, int i)
{
	while (line && line[i] && line[i] != ' ' && line[i] != ';')
		i++;
	return (i);
}

/**
 * Функция пропускает пробелы
*/

int skip_spaces(const char *line, int i)
{
	while (line && line[i] && line[i] == ' ')
		i++;
	return (i);
}

/**
 * Функция добавляет символ в строку
*/

char	 *add_chr(char *str, char c)
{
	char	*new_str;
	size_t	size;
	int 	i;

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
	return (new_str);
}

/**
 * Функция читает строку посимвольно и собирает прочитанное в аргумент
*/

int get_next_arg(char *line, int i, char **tmp_line)
{
	int	flag;

	flag = 0;
	while (line[i])
	{
		if (line[i] == '\\' && !(flag & QUOTE))
		{
			flag = flag & SHIELD;
			i++;
		}
		if (line[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
		{
			flag = flag ^ DOUBLE_QUOTE;
			i++;
		}
		if (line[i] == '\'' && !(flag & SHIELD) && !(flag & DOUBLE_QUOTE))
		{
			flag = flag ^ QUOTE;
			i++;
		}
		if (line[i] && ((line[i] != ' ' && line[i] != ';' && line[i] != '|') 
			|| flag))
			*tmp_line = add_chr(*tmp_line, line[i]);
		else
			return (i);
		i++;
		if (line[i])
			flag = flag & ~(SHIELD);
	}
	return (i);
}
