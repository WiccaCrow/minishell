#include "../includes/minishell.h"

/************************************
 * 				exec_pwd			*
 * **********************************
 * 		Print the full filename of 
 * 		the current working directory.
*/

void	exec_pwd(t_all *all)
{
	write((*(all->commands))->output_fd, all->pwd, ft_strlen(all->pwd));
	write((*(all->commands))->output_fd, "\n", 1);
	all->completion_code = 0;
}