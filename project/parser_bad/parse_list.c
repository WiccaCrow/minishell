#include "minishell.h"

int	args_list_to_arr(t_list **args, t_command *command)
{
	size_t	size;
	t_list	*tmp;
	int 	i;

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
		while(tmp)
		{
			command->args[i++] = (char *) tmp->content;
			tmp = tmp->next;
		}
		command->args[i] = NULL;
		return (0);
	}
	return (1);
}

int 	is_redirect(t_list *curr)
{
	if (curr && curr->content && \
	ft_strchr("><", (int)*(char *)curr->content))
		return (1);
	return (0);
}

int 	set_redirect_type(t_list *curr, t_command *command)
{
	char *str;
	
	if (curr && curr->content && command)
	{
		str = (char *)curr->content;
		if (str[0] == '>')
		{
			if (str[1] && str[1] == '>' && (str[2] == 0 || ft_isalpha(str[2])))
				command->redirect_type = APPEND;
			else if (str[1] == 0 || ft_isalpha(str[1]))
				command->redirect_type = WRITE;
		}
		else if (str[0] == '<' && (str[1] == 0 || ft_isalpha(str[1])))
			command->redirect_type = READ;
		if (command->redirect_type)
			return (1);
	}
	return (0);	
}

char *get_file_name(t_list *curr, t_command *command)
{
	char *str;

	if (curr && curr->content && command)
	{
		str = (char *) curr->content;
		if (command->redirect_type & APPEND || command->redirect_type & READ)
		{
			if (str[1])
				str++;
			else if (curr->next && curr->next->content)
				str = (char *) curr->next->content;
			else
				return (0);
		} else
		{
			if (str[2])
				str += 2;
			else if (curr->next && curr->next->content)
				str = (char *) curr->next->content;
			else
				return (0);
		}
		return (ft_strdup(str));
	}
	return (0);
}


t_list *handle_redirect(t_list *curr, t_list **list, t_command *command)
{
	char *file_name;
	
	if (set_redirect_type(curr, command)) // вернет 0 если редирект неправильный
	{
		file_name = get_file_name(curr, command);
		if (file_name)
		{
			if (command->redirect_type & APPEND)
				command->output_fd = open(file_name, O_CREAT | O_WRONLY | 
					O_APPEND, 0644);
			if (command->redirect_type & WRITE)
				command->output_fd = open(file_name, O_CREAT | O_WRONLY |
					O_TRUNC, 0644);
			if (command->redirect_type & READ)
				command->input_fd = open(file_name, O_RDONLY , 0644)
		}
		remove_redirect_from_list()
	}
}


int 	get_redirects(t_command *command, t_list **list)
{
	t_list *curr;
	
	if (list)
	{
		curr = *list;
		while (curr)
		{
			if (is_redirect(curr))
				curr = handle_redirect(curr, list, command);
			else
				curr = curr->next;
		}
		return (1);
	}
	return (0);
}

int		parse_list(t_command *command, t_list **list)
{
	get_redirects(command, list);
	set_command_flag(command, list);
	args_list_to_arr(list, command);
}