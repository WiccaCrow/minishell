#include "minishell.h"

/************************************
 * 	1.3.5.4.	exec_pwd			*
 * **********************************
 * 		Print the full filename of 
 * 		the current working directory.
*/

void	exec_pwd(t_all *all, t_command *tmp)
{
	write(tmp->output_fd, all->pwd, ft_strlen(all->pwd));
	write(tmp->output_fd, "\n", 1);
	g_completion_code = 0;
}
