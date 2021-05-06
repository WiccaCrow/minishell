#include "../includes/minishell.h"

int exec_echo(t_all *all)
{
	int i;
	int ret;
	// all->flag_command
		write(1, "test exec_echo\n", 16);
	i = 1;
	ret = 0;
	if (all)
		ret = 1;
	printf("%d\n", all->flag_command);
	// if (all->command.command[i])
	// {
	// 	if (ft_strnstr(all->command.command[i], "-n", 3))
	// 		i++;
	// 	while (all->command.command[i])
	// 	{
	// 		ret += (int) write(STDOUT_FILENO, all->command.command[i], ft_strlen
	// 				(all->command.command[i]));
	// 		i++;
	// 		if (all->command.command[i])
	// 			ret += (int) write(STDOUT_FILENO, " ", 1);
	// 	}
	// 	if (ft_strnstr(all->command.command[1], "-n", 3))
	// 		return (ret > 0);
	// }
	// ret += (int) write(STDOUT_FILENO, "\n", 1);
	return (ret > 0);	
}
