#include "../includes/minishell.h"

int	get_args_list(t_list **args, t_all *all)
{
	int		i;
	char	*tmp_line;
	t_list	*lst_new;
	
	i = skip_command(all->line);
	i = skip_spaces(all->line, i);
	tmp_line = NULL;
	while (all->line[i] && all->line[i] != ';')
	{
		i = get_next_arg(all->line, i, &tmp_line);
		i = skip_spaces(all->line, i);
		if (tmp_line)
		{
			lst_new = ft_lstnew(ft_strdup(tmp_line));
			ft_lstadd_back(args, lst_new);
			free(tmp_line);
			tmp_line = NULL;
		}
	}
	return (0);
}

int	args_list_to_arr(t_list **args, t_all *all)
{
	size_t	size;
	t_list	*tmp;
	int 	i;
	
	size = ft_lstsize(*args) + 1;
	all->args = (char **)malloc(sizeof(char *) * size);
	if (all->args)
	{
		if (!(*args))
		{
			all->args[0] = NULL;
			return (0);
		}
		tmp = *args;
		i = 0;
		while(tmp)
		{
			all->args[i++] = (char *) tmp->content;
			tmp = tmp->next;
		}
		all->args[i] = NULL;
		return (0);
	}
	return (1);
}
int clear_list(t_list **args)
{
	t_list *tmp;
	t_list *tmp2;
	
	tmp = *args;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	free(args);
	return (0);
}

int get_args(t_all *all)
{
	t_list	**args;

	args = (t_list **)malloc(sizeof (t_list *));
	if (args)
	{
		*args = NULL;
		get_args_list(args, all);
		args_list_to_arr(args, all);
		clear_list(args);
		return (1);
	}
	return (0);
}
