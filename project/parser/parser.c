#include "../includes/minishell.h"

int parser(char *line, t_command *command)
{
	char	**strings;
	
	strings = ft_split(line, ' ');
	if (strings)
	{
		command->command = strings;
		return (0);
	}
	return (1);
}