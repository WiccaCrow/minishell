#include "minishell.h"

int	add_wclist_to_args(t_list **args, t_list **wc_list)
{
	t_list	*tmp;

	if (args && wc_list)
	{
		if (*args)
		{
			tmp = ft_lstlast(*args);
			tmp->next = *wc_list;
		}
		else
			*args = *wc_list;
		free(wc_list);
		return (1);
	}
	return (0);
}

int	is_wildcard(const char *word)
{
	int	i;
	int	flag;

	if (word)
	{
		flag = 0;
		i = -1;
		while (word[++i])
		{
			if (word[i] == '\\' && !(flag & QUOTE) && !(flag & SHIELD))
				flag = flag | SHIELD;
			else if (word[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
				flag = flag ^ DOUBLE_QUOTE;
			else if (word[i] == '\'' && !(flag & SHIELD) && \
				!(flag & DOUBLE_QUOTE))
				flag = flag ^ QUOTE;
			else if ((word[i] == '*') && !flag)
				return (1);
			else if ((flag & SHIELD))
				flag = flag & ~(SHIELD);
		}
	}
	return (0);
}

int	fill_new_args(t_all *all, t_list ***args, t_list **new_args)
{
	t_list	*tmp;
	t_list	**wc_list;

	tmp = **args;
	while (tmp)
	{
		if (is_wildcard((char *)tmp->content))
		{
			wc_list = wildcard_open_read_dir(all->pwd, (char *)tmp->content);
			if (wc_list && *wc_list)
			{
				add_wclist_to_args(new_args, wc_list);
				ft_free((void **)&(tmp->content));
			}
			else
				ft_lstadd_back(new_args,
					ft_lstnew(((char *) tmp->content)));
		}
		else
			ft_lstadd_back(new_args,
				ft_lstnew(((char *) tmp->content)));
		tmp = tmp->next;
	}
	return (0);
}

int	wildcard_handle(t_all *all, t_list ***args)
{
	t_list	**new_args;

	new_args = (t_list **)ft_calloc(1, sizeof(t_list *));
	if (args && *args && new_args)
	{
		fill_new_args(all, args, new_args);
		clear_list2(*args);
		*args = new_args;
	}
	return (0);
}
