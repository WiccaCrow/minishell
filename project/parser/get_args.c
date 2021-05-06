#include "../includes/minishell.h"

static int skip_command(const char *line)
{
	int	i;
	
	i = 0;
	while (line && line[i] && line[i] != ' ')
		i++;
	return (i);
}

int get_next_arg(char *line, int i, char **tmp_line)
{
	int	flag;
	
	while (is_end_of_arg(line[i]))
	return (0);
}

int	get_args_list(t_list **args, t_all *all)
{
	int i;
	char *tmp_line;
	
	i = skip_command(all->line);
	tmp_line = NULL;
	while (all->line[i])
	{
		i = get_next_arg(all->line, i, &tmp_line);
		ft_lstadd_back(args, ft_lstnew(tmp_line));
	}
	return (0);
}

int	args_list_to_arr();
int clear_list();

int get_args(t_all *all)
{
	t_list	**args;
	
	args = (t_list **)malloc(sizeof (t_list *));
	if (args)
	{
		get_args_list(args, all);
		args_list_to_arr(args, all);
		clear_list(args);
		return (1);
	}
	return (0);
}
