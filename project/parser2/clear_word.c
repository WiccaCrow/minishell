#include "minishell.h"

char *clear_word(char *word)
{
	int		i;
	int		flag;
	char	*new_word;

	i = 0;
	flag = 0;
	new_word = NULL;
	while (word[i])
	{
		if (word[i] == '\\' && !(flag & QUOTE) && !(flag & SHIELD))
			flag = flag | SHIELD;
		else if (word[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
			flag = flag ^ DOUBLE_QUOTE;
		else if (word[i] == '\'' && !(flag & SHIELD) && !(flag & DOUBLE_QUOTE))
			flag = flag ^ QUOTE;
		else
		{
			new_word = add_chr(new_word, word[i]);
			if ((flag & SHIELD))
				flag = flag & ~(SHIELD);
		}
		i++;
	}
	ft_free((void **)&word);
	return (new_word);
}

int clear_words(t_list **args)
{
	t_list	*tmp;
	
	if (args)
	{
		tmp = *args;
		while (tmp)
		{
			tmp->content = clear_word(tmp->content);
			tmp = tmp->next;
		}
		return (1);
	}
	return (0);
}