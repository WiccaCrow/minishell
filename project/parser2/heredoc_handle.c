#include "minishell.h"

int heredoc_handle(t_all *all, int i)
{
	int 		fd;
	char 		*word;
	t_list		**args;

	fd = 0;
	args = (t_list **)ft_calloc(1, sizeof(t_list *));
	if (args)
	{
		while (all->line[i] && all->line[i] != ';' && all->line[i] != '|')
		{
			word = NULL;
			i = get_next_word_lc(all->line, i, &word);
			i = skip_spaces(all->line, i);
			ft_lstadd_back(args, ft_lstnew(ft_strdup(word)));
			free(word);
		}
		fd = do_heredoc_redirects(args);
	}
	return (fd);
}

