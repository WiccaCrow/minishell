#include "minishell.h"

int	do_heredoc_redirects(t_list **args)
{
	t_list	*tmp;
	int		redirect_type;
	int		fd;

	fd = 0;
	if (args)
	{
		tmp = *args;
		while (tmp)
		{
			redirect_type = set_redirect((char *)tmp->content);
			if (redirect_type & HEREDOC && tmp->next)
				fd = open_tmp_file((char *)tmp->next->content);
			tmp = tmp->next;
		}
		ft_lstclear(args, free);
		ft_free((void *)&args);
	}
	return (fd);
}
