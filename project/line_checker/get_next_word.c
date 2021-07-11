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
	int	i;

	i = 0;
	while (tmp_line && ft_isdigit((int)tmp_line[i]))
		i++;
	if (tmp_line && tmp_line[i] == '>' && c != '>')
		return (1);
	if (tmp_line && tmp_line[i] == '>' && tmp_line[i + 1] == '>')
		return (1);
	if (tmp_line && tmp_line[i] == '<' && c != '<')
		return (1);
	if (tmp_line && tmp_line[i] == '<' && tmp_line[i + 1] == '<')
		return (1);
	return (0);
}

int is_word_num(const char *word)
{
	int	i;

	i = 0;
	while (word && ft_isdigit((int)word[i]))
		i++;
	if (word[i] == '>' || word[i] == '<')
		i++;
	return (word[i] == 0);
}

int is_word_ended(char c, const char *tmp_line, int flag)
{
	if (is_token(tmp_line) && !flag)
		return (1);
	if (is_redirect(c, tmp_line) && !flag)
		return (1);
	if (tmp_line && *tmp_line && !is_word_num(tmp_line) && \
		ft_strchr(">;|&", (int)c) && !flag)
		return (1);
	return (0);
}

int	get_next_word_lc(char *line, int i, char **tmp_line)
{
	int	flag;

	flag = 0;
	while (line[i] && !is_word_ended(line[i], *tmp_line, flag))
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
			return (i);
		i++;
	}
	return (i);
}
