#include "minishell.h"

static int is_token(char *line)
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
	return (0);
}

static int	get_next_word(char *line, int i, char **tmp_line)
{
	int	flag;

	flag = 0;
	while (line[i] && !is_token(*tmp_line))
	{
		if (line[i] == '\\' && !(flag & QUOTE) && !(flag & SHIELD))
		{
			flag = flag | SHIELD;
			i++;
		}
		else if (line[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
		{
			flag = flag ^ DOUBLE_QUOTE;
			i++;
		}
		else if (line[i] == '\'' && !(flag & SHIELD) && !(flag & DOUBLE_QUOTE))
		{
			flag = flag ^ QUOTE;
			i++;
		}
		else if ((line[i] != ' ') || flag)
		{
			*tmp_line = add_chr(*tmp_line, line[i++]);
			if (line[i])
				flag = flag & ~(SHIELD);
		}
		else
			return (i);
	}
	return (i);
}

char	set_type(const char *word)
{
	int type;
	
	type = set_redirect(word);
	if (type & NO_FILENAME)
		return (NOFILE_REDIRECT);
	if (word[0] == ';' || word[0] == '|' || word[0] == '&')
		return (TOKEN);
	return (WORD);
	
}

int	check_word(char *word, char *prev_type)
{
	char	curr_type;
	
	curr_type = set_type(word);
	if (curr_type & WORD)
	{
		*prev_type = curr_type;
		return (1);
	}
	if (curr_type & TOKEN && (*prev_type & TOKEN || *prev_type & 
	NOFILE_REDIRECT))
	{
		*prev_type = curr_type;
		return (0);
	}
	*prev_type = curr_type;
	return (1);
}

int check_line(t_all *all)
{
	int		i;
	char	*word;
	char 	prev_type;

	if (all && all->line)
	{
		i = skip_spaces(all->line, 0);
		prev_type = TOKEN;
		while (all->line[i])
		{
			word = NULL;
			i = get_next_word(all->line, i, &word);
			if (!check_word(word, &prev_type) && write(STDOUT_FILENO, 
				SYN_ERR, 47) && write(STDOUT_FILENO, word, ft_strlen(word)) 
				&& write(STDOUT_FILENO, "\'\n", 2))
			{
				all->completion_code = 258;
				return (0);
			}			i = skip_spaces(all->line, i);
		}
	}
	return (1);
}