#include "../includes/minishell.h"

/************************************
 * 				exec_pwd			*
 * **********************************
 * 		Print the full filename of 
 * 		the current working directory.
*/

void	exec_pwd(t_all *all)
{
		write(STDOUT_FILENO, all->pwd, ft_strlen(all->pwd));
		write(STDOUT_FILENO, "\n", 1);
}