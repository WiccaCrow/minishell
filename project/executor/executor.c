#include "../includes/minishell.h"

int command_not_found(t_all *all)
{
	int ret;

	write(1, "minishell: ", 12);
	ret = 0;
	while (all->line[ret] && all->line[ret] != ' ')
		++ret;
	write(1, all->line, ret);
	ret += (int) write(STDOUT_FILENO, COM_NOT_FOUND, ft_strlen(COM_NOT_FOUND));
	free(all->line);
	all->line = NULL;
	return (ret);
}

/************************************
 * 		1.4. executor				*
 * **********************************
 * Look README for more information (operation flags).
 * Accepts a data-ready structure.
 * Prints the result or error to standard output as
 * needed.
*/

int executor(t_all *all)
{
	if (all->flag_command == not_found)
		return (command_not_found(all));
	if (all->flag_command == exit_shell)
		exit_clean(all);
	if (all->flag_command == echo)
		exec_echo(all);
	else
		return (write(1, "other command\n", 15));
	return (1);
}