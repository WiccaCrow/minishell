#include "minishell.h"

/************************************
 * 		1.3.5.  executor			*
 * **********************************
*/
/* Description:
 * Checks the command flag (enum) and sends the command for execution.
 * Prints the result or error to standard output as needed.
 * 
 * Contains functions:
 * 		1.3.5.1. command_not_found;
 * 			Prints the result or error to standard output as needed. Bash
 * 			standart erorr $? 127.
 * 		1.3.5.2. exec_echo;
 * 		1.3.5.3. exec_cd;
 * 		1.3.5.4. exec_pwd;
 * 		1.3.5.5. exec_env;
 * 		1.3.5.6. exec_export;
 * 		1.3.5.7. exec_unset;
 * 		1.3.5.8.   exit_clean;
*/

int	executor(t_all *all, t_command *tmp)
{
	if (tmp->flag_command == not_found)
		command_not_found(all, tmp);
	else if (tmp->flag_command == exit_shell)
		exec_exit(all, tmp);
	else if (tmp->flag_command == echo)
		exec_echo(tmp);
	else if (tmp->flag_command == cd)
		exec_cd(all, tmp);
	else if (tmp->flag_command == pwd)
		exec_pwd(all, tmp);
	else if (tmp->flag_command == env)
		exec_env(all, tmp);
	else if (tmp->flag_command == export)
		exec_export(all, tmp);
	else if (tmp->flag_command == unset)
		exec_unset(all, tmp);
	return (1);
}

/************************************
 * 		1.3.5.1. command_not_found	*
 * **********************************
*/
/* Description:
 * Prints the result or error to standard output as needed. Bash standart
 * erorr $? sets 127.
 * 
 * Contains functions:
 * 1.3.5.1.1. 	executable;
 * 1.3.5.1.2. 	print_command_not_found;
 * libft. 		ft_strlen;
*/

void	command_not_found(t_all *all, t_command *tmp)
{
	if (!(tmp->end_flag & PIPE || tmp->end_flag & START_PIPE))
		g_completion_code = 0;
	if (!g_completion_code && executable(all, tmp) == 0 && !g_completion_code)
		return ;
	if (!g_completion_code)
		print_command_not_found(tmp);
}

/****************************************
 * 1.3.5.1.2. print_command_not_found	*
 * **************************************
*/
/* Description:
 * Prints the result or error to standard output. Bash standart erorr $?
 * sets 127.
 * 
 * Contains functions:
 * libft. ft_strlen;
*/

void	print_command_not_found(t_command *tmp)
{
	write(STDERR_FILENO, "minishell: ", 12);
	write(STDERR_FILENO, tmp->args[0], ft_strlen(tmp->args[0]));
	write(STDERR_FILENO, COM_NOT_FOUND, ft_strlen(COM_NOT_FOUND));
	g_completion_code = 127;
}

/************************************
 * 		close_fd_output_input		*
 * **********************************
*/
/* Description:
 * close fd and set it to 1 and 0.
*/

void	close_fd_output_input(t_command *tmp)
{
	if (tmp->output_fd != 1)
	{
		close(tmp->output_fd);
		tmp->output_fd = 1;
	}
	if (tmp->input_fd != 0)
	{
		close(tmp->input_fd);
		tmp->input_fd = 0;
	}
}
