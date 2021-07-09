#include "minishell.h"

static int	is_token(const char *line)
{
	if (!line)
		return (0);
	if (!ft_strncmp(line, ";", 2))
		return (1);
	if (!ft_strncmp(line, ";;", 3))
		return (2);
	if (!ft_strncmp(line, "|", 2))
		return (3);
	if (!ft_strncmp(line, "&&", 3))
		return (4);
	if (!ft_strncmp(line, "||", 3))
		return (5);
	if (!ft_strncmp(line, ">>", 2))
		return (6);
	if (!ft_strncmp(line, "<<", 2))
		return (7);
	return (0);
}

static int	is_redirect(char c, const char *tmp_line)
{
	if (tmp_line && tmp_line[0] == '>' && c != '>')
		return (1);
	if (tmp_line && tmp_line[0] == '<' && c != '<')
		return (1);
	return (0);
}

int	get_next_word_lc(char *line, int i, char **tmp_line)
{
	int	flag;

	flag = 0;
	while (line[i] && !is_token(*tmp_line) && !is_redirect(line[i], *tmp_line))
	{
		if (line[i] == '\\' && !(flag & QUOTE) && !(flag & SHIELD))
			flag = flag | SHIELD;
		else if (line[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
			flag = flag ^ DOUBLE_QUOTE;
		else if (line[i] == '\'' && !(flag & SHIELD) && !(flag & DOUBLE_QUOTE))
			flag = flag ^ QUOTE;
		else if ((line[i] != ' ') || flag)
		{
			*tmp_line = add_chr(*tmp_line, line[i]);
			if ((flag & SHIELD))
				flag = flag & ~(SHIELD);
		}
		else
		{
			return (i);
		}
		i++;
	}
	return (i);
}
