#include "../includes/minishell.h"

int executor(t_command *command)
{
	if (ft_strnstr(command->command[0], ECHO, 4))
	{
//		printf("Hi from exec, command:\n\"%s\"\n", command->command[0]);
		return (exec_echo(command));
	}
	return (0);
}