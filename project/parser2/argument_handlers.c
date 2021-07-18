#include "minishell.h"

int	args_list_to_arr2(t_list **args, t_command *command)
{
	size_t	size;
	t_list	*tmp;
	int		i;

	size = ft_lstsize(*args) + 1;
	command->args = (char **)malloc(sizeof(char *) * size);
	if (command->args)
	{
		if (!(*args))
		{
			command->args[0] = NULL;
			return (0);
		}
		tmp = *args;
		i = 0;
		while (tmp)
		{
			command->args[i++] = (char *) tmp->content;
			tmp = tmp->next;
		}
		command->args[i] = NULL;
		return (0);
	}
	return (1);
}

int	clear_list2(t_list **args)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *args;
	while (tmp)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
		tmp2 = NULL;
	}
	free(args);
	args = NULL;
	return (0);
}

int	remove_first(t_list **args)
{
	t_list	*tmp;

	if (args)
	{
		tmp = *args;
		if (tmp)
		{
			*args = tmp->next;
			free(tmp->content);
			tmp->content = NULL;
			free(tmp);
			tmp = NULL;
		}		
	}
	return (0);
}
