#include "minishell.h"

static int	free_command(t_command *command)
{
	int i;

	i = -1;
	free_char_array(command->args);
	if (command->args)
		while (command->args[++i])
			ft_free((void **)&(command->args[i]));
	command->args = NULL;
	free(command);
	command = NULL;
	return (0);
}

int	free_commands(t_command **commands)
{
	t_command	*tmp;
	t_command	*tmp2;

	if (commands)
	{
		tmp = *commands;
		while (tmp)
		{
			close_fd_output_input(tmp);
			tmp2 = tmp;
			tmp = tmp->next;
			free_command(tmp2);
		}
		if (commands)
			free(commands);
		commands = NULL;
	}
	return (0);
}
