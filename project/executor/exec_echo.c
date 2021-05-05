#include "../includes/minishell.h"

int exec_echo(t_command *command)
{
	int i;
	int ret;
	
	i = 1;
	ret = 0;
	if (ft_strnstr(command->command[i], "-n", 3))
		i++;
	while (command->command[i])
	{
		ret += (int) write(STDOUT_FILENO, command->command[i], ft_strlen
			(command->command[i]));
		i++;
	}
	if (ft_strnstr(command->command[1], "-n", 3))
		return (ret > 0);
	ret += (int) write(STDOUT_FILENO, "\n", 1);
	return (ret > 0);	
}
