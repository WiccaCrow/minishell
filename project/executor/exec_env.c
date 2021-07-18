#include "minishell.h"

/************************************
 * 	1.3.5.5. exec_env				*
 * **********************************
*/
/* Description:
 * 		Print my env array.
 * 
 * Contains functions:
 * libft.	ft_strlen;
 * libft.	ft_strchr;
*/

void	exec_env(t_all *all, t_command *tmp)
{
	int	i;

	i = -1;
	g_completion_code = 0;
	if (tmp->args[0])
	{
		write(tmp->output_fd, "env: must be without any ", 25);
		write(tmp->output_fd, "options and any arguments\n", 26);
		g_completion_code = 127;
	}
	else
	{
		while (all->env[++i])
		{
			if (ft_strchr(all->env[i], '='))
			{
				write(tmp->output_fd, all->env[i],
					ft_strlen(all->env[i]));
				write(tmp->output_fd, "\n", 1);
			}
		}
	}
}
