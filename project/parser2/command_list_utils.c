#include "minishell.h"

static int	free_command(t_command *command)
{
printf("test 4.1\n");
	if (command->args)
	{
		free_char_array(command->args);
		command->args = NULL;
	}
printf("test 4.2\n");
	if  (command)
	{
printf("test 4.3\n");
		free(command);
printf("test 4.4\n");
		command = NULL;
	}
	return (0);
}

int	free_commands(t_command **commands)
{
	t_command	*tmp;
	t_command	*tmp2;
printf("test 1\n");
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
printf("test 6\n");
		if (commands)
			free(commands);
		commands = NULL;
	}
printf("test 7\n");
	return (0);
}
