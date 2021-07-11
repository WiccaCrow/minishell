#include "minishell.h"

/**
 * Функция находит первый неэкранированный символ ';' в строке 
*/

int	get_semicolon(const char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '\\' && !(flag & QUOTE) && !(flag & SHIELD))
			flag = flag | SHIELD;
		else if (line[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
			flag = flag ^ DOUBLE_QUOTE;
		else if (line[i] == '\'' && !(flag & SHIELD) && \
				!(flag & DOUBLE_QUOTE))
			flag = flag ^ QUOTE;
		else if (line[i] == ';' && !flag)
			return (i);
		else if ((flag & SHIELD))
			flag = flag & ~(SHIELD);
		i++;
	}
	return (0);
}

/**
 * Функция обрезает начало строки до первого неэкранированного ';' в 
 * строке 
*/

int	crop_line(char **line)
{
	int		i;
	int		j;
	char	*new_line;

	i = get_semicolon(*line);
	if (i)
	{
		new_line = (char *)ft_calloc((ft_strlen(&((*line)[i]))), sizeof (char));
		if (new_line)
		{
			i = skip_spaces(*line, ++i);
			j = 0;
			while ((*line)[i])
				new_line[j++] = (*line)[i++];
			free(*line);
			*line = new_line;
			return (1);
		}
	}
	free(*line);
	*line = NULL;
	return (i);
}
