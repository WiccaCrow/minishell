#include "minishell.h"

char	set_type(const char *word)
{
	int	type;

	type = set_redirect(word);
	if (type & NO_FILENAME)
		return (NOFILE_REDIRECT);
	if (word[0] == ';' || word[0] == '|' || word[0] == '&' || word[0] == '>' \
	|| word[0] == '<')
		return (TOKEN);
	return (WORD);
}

static int	token_err(char curr, char prev)
{
	if (!prev && curr & TOKEN)
		return (1);
	if (prev & TOKEN && curr & TOKEN)
		return (1);
	if (prev & NOFILE_REDIRECT && curr & NOFILE_REDIRECT)
		return (1);
	return (0);
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
	if (token_err(curr_type, *prev_type))
	{
		*prev_type = curr_type;
		return (0);
	}
	*prev_type = curr_type;
	return (1);
}

int	check_line(t_all *all)
{
	int		i;
	char	*word;
	char	prev_type;

	if (all && all->line)
	{
		i = skip_spaces(all->line, 0);
		prev_type = 0;
		while (all->line[i])
		{
			word = NULL;
			i = get_next_word_lc(all->line, i, &word);
			if (!check_word(word, &prev_type))
			{
				g_completion_code = 2 + 256 * (word[0] == ';');				
				write(STDOUT_FILENO, SYN_ERR, 47);
				write(STDOUT_FILENO, word, ft_strlen(word));
				write(STDOUT_FILENO, "\'\n", 2);
				return (all->check_line = 0);
			}
			i = skip_spaces(all->line, i);
		}
	}
	return (all->check_line = 1);
}
