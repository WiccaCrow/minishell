#include "minishell.h"

int	ft_putchar(int c)
{
	return ((int)write(STDOUT_FILENO, &c, 1));
}

size_t	copy_line_begin(char *dest, const char *src, size_t end_pos)
{
	size_t	i;

	i = 0;
	while (src && src[i] && i < end_pos)
	{
		dest[i] = src[i];
		i++;
	}
	return (i);
}

size_t	copy_line_end(char *dest, const char *src, size_t start_pos)
{
	size_t	i;

	i = start_pos;
	while (src && src[i - 1])
	{
		dest[i] = src[i - 1];
		i++;
	}
	dest[i] = 0;
	return (i);
}

int	add_chr_to_pos(t_line *line, char c)
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
		i = copy_line_begin(new_str, line->curr_line, line->pos);
		new_str[i++] = c;
		copy_line_end(new_str, line->curr_line, i);
		free(line->curr_line);
		line->curr_line = new_str;
		size = write(STDIN_FILENO, &new_str[line->pos], \
			ft_strlen (&new_str[line->pos])) - 1;
		while (size--)
			tputs(cursor_left, 1, ft_putchar);
		line->pos++;
		line->hist_pos = line->hist_len;
		ft_free((void **)&line->tmp_line);
		return (1);
	}
	return (0);
}

int	remove_chr_from_pos(t_line *line)
{
	char	*new_str;
	size_t	size;
	size_t	i;

	if (line->pos && !tputs(cursor_left, 1, ft_putchar) && \
		!tputs(delete_character, 1, ft_putchar))
	{
		size = gnl_strlen(line->curr_line);
		new_str = (char *)ft_calloc(size, sizeof(char));
		if (new_str)
		{
			i = copy_line_begin(new_str, line->curr_line, line->pos - 1);
			while (line->curr_line && line->curr_line[++i - 1])
				new_str[i - 1] = line->curr_line[i];
			free(line->curr_line);
			line->curr_line = new_str;
			line->pos--;
			line->hist_pos = line->hist_len;
			ft_free((void **)&line->tmp_line);
			return (1);
		}
	}
	return (0);
}
