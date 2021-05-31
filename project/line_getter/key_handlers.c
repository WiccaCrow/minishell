#include "../includes/minishell.h"

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
	return (flag);
}

int		enter_handle(char **line, char **curr_line, size_t *pos)
{
	if (check_end_of_input(*line))
		return (1);
	else
	{
		*line = gnl_strjoin(*line, *curr_line);
		free(*curr_line);
		*curr_line = NULL;
		*pos = 0;
		write(STDOUT_FILENO, "\n> ", 3);
	}
	return (0);
}

int 	key_right_handle(char *line, size_t *pos)
{
	if (*pos < ft_strlen(line))
	{
		(*pos)++;
		tputs(cursor_right, 1, ft_putchar);
	}
	return (0);
}

int 	key_left_handle(size_t *pos)
{
	if (*pos > 0)
	{
		(*pos)--;
		tputs(cursor_left, 1, ft_putchar);
	}
	return (0);
}
