#include "../includes/minishell.h"

static int skip_command(const char *line)
{
	int	i;

	i = 0;
	while (line && line[i] && line[i] != ' ')
		i++;
	return (i);
}

static int skip_spaces(const char *line, int i)
{
	while (line && line[i] && line[i] == ' ')
		i++;
	return (i);
}

static char *add_chr(char *str, char c)
{
	char	*new_str;
	size_t	size;
	int 	i;
	
	size = gnl_strlen(str) + 2;
	new_str = (char *)malloc(sizeof(char) * size);
	if (new_str)
	{
		i = 0;
		while (str && str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i++] = c; 
		new_str[i] = 0; 
	}
	return (new_str);
}

int get_next_arg(const char *line, int i, char **tmp_line)
{
	int	flag;

	flag = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
			flag = flag & SHIELD;
			i++;
		}
		if (line[i] == '\"')
		{
			flag = flag ^ DOUBLE_QUOTE;
			i++;
		}
		if (line[i] == '\'')
		{
			flag = flag ^ QUOTE;
			i++;
		}
		if (line[i] != ' ' && !flag)
			*tmp_line = add_chr(*tmp_line, line[i]);
		else
			return (i);
		flag = flag & ~(SHIELD);
		i++;
	}
	return (i);
}

int	get_args_list(t_list **args, t_all *all)
{
	int		i;
	char	*tmp_line;
	t_list	*lst_new;
	
	i = skip_command(all->line);
	i = skip_spaces(all->line, i);
	tmp_line = NULL;
	while (all->line[i])
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
