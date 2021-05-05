#include "../includes/minishell.h"

int command_not_found()
{
	int ret;
	
	ret = 0;
	ret += (int) write(STDOUT_FILENO, COM_NOT_FOUND, ft_strlen(COM_NOT_FOUND));
	return (ret);
}

int	is_command(const char *str, const char *command)
{
	int i;
	
	if (str && command)
	{
		i = 0;
		while (str[i] && command[i])
		{
			if (str[i] != command[i])
				return (0);
			i++;
		}
		if (str[i] != command[i])
			return (0);
		return (1);
	}
	return (0);
}

int executor(t_all *all)
{
	if (is_command(all->command.command[0], ECHO))
		return (exec_echo(all));
	return (command_not_found());
}