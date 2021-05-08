#include "../includes/minishell.h"

/************************************
 * 		1.4.1. command_not_found	*
 * **********************************
 * Prints the result or error to standard 
 * output as needed. Bash standart erorr $? 127.
 * 
 * functions:
 * libft. ft_strlen;
*/

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
	return (127);
}

/************************************
 * 		1.4. executor				*
 * **********************************
 * Checks the command flag (enum) and sends the 
 * command for execution.
 * Prints the result or error to standard output as
 * needed.
 * 
 * function:
 * 1.4.1. command_not_found;
 * 		Prints the result or error to standard 
 * 		output as needed. Bash standart erorr $? 127.
 * 1.4.2. exec_echo;
 * 		execution command 'echo'
 * 1.5.   exit_clean;
*/

int executor(t_all *all)
{
	if (all->flag_command == not_found)
		return (all->return_code = command_not_found(all));
	if (all->flag_command == exit_shell)
		exit_clean(all);
	if (all->flag_command == echo)
		exec_echo(all);
	else
		return (write(1, "other command\n", 15));
	return (1);
}

//echo m$PWD$USER$