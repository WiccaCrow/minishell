#include "../includes/minishell.h"

/************************************
 * 			exec_env				*
 * **********************************
*/ 
/* Description:
 * 		Print my env array.
 * 
 * Contains functions:
 * libft.	ft_strlen;
 * libft.	ft_strchr;
*/

void	exec_env(t_all *all)
{
	int	i;

	i = -1;
	all->completion_code = 0;
	if (all->args[0])
	{
		write((*(all->commands))->output_fd, "env: must be without any ", 26);
		write((*(all->commands))->output_fd, "options and any arguments\n", 27);
		all->completion_code = 127;
	}
	else
		while (all->env[++i])
		{
			if (ft_strchr(all->env[i], '='))
			{
				write((*(all->commands))->output_fd, all->env[i], ft_strlen(all->env[i]));
				write((*(all->commands))->output_fd, "\n", 1);
			}
		}
}
