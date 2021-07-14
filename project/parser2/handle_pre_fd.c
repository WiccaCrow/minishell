#include "minishell.h"

int handle_pre_fd(t_command *command, char *word)
{
	int fd;
	
	fd = ft_atoi(word);
	if (fd > FOPEN_MAX)
		return (!executable_error_print(word, BAD_FD, 1));
	if (fd != 1)
	{
		command->redirect_type |= PRE_FD;
		if (command->redirect_type & WRITE || command->redirect_type & APPEND)
			command->output_fd = fd;
		else
			command->input_fd = fd;
	}
	return (1);
}