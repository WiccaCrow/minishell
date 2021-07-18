#include "minishell.h"

static int	check_end_of_input(const char *line)
{
	int	i;
	int	flag;

	flag = 0;
	if (line)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '\\' && !(flag & QUOTE) && !(flag & SHIELD))
				flag = flag | SHIELD;
			else if (line[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
				flag = flag ^ DOUBLE_QUOTE;
			else if (line[i] == '\'' && !(flag & SHIELD) && \
				!(flag & DOUBLE_QUOTE))
				flag = flag ^ QUOTE;
			else if ((flag & SHIELD))
				flag = flag & ~(SHIELD);
			i++;
		}
		return (!flag);
	}
	return (1);
}

int	enter_handle(t_line *line)
{
	if (line->main_line)
		line->main_line = gnl_strjoin(line->main_line, "\n");
	line->main_line = gnl_strjoin(line->main_line, line->curr_line);
	free(line->curr_line);
	line->curr_line = NULL;
	if (check_end_of_input(line->main_line))
		return (1);
	else
	{
		line->pos = 0;
		write(STDOUT_FILENO, "\n> ", 3);
	}
	return (0);
}

int 	key_right_handle(t_line *line)
{
	if (line->pos < gnl_strlen(line->curr_line))
	{
		line->pos++;
		tputs(cursor_right, 1, ft_putchar);
	}
	return (0);
}

int 	key_left_handle(t_line *line)
{
	if (line->pos > 0)
	{
		line->pos--;
		tputs(cursor_left, 1, ft_putchar);
	}
	return (0);
}

int	control_d_handle(t_line *line)
{
	if (line)
	{
		if (line->curr_line && *line->curr_line)
			return (0);
		else if (line->main_line && *line->main_line)
		{
			write(STDOUT_FILENO, UNEXP_EOF UNEXP_EOF2, 104);
			free(line->main_line);
			line->main_line = ft_strdup("");
			return (1);
		}
		else
			line->main_line = ft_strdup("exit");
		return (2);
	}
	return (0);
}
