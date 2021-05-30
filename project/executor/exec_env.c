#include "../includes/minishell.h"

/************************************
 * 			exec_env				*
 * **********************************
 * Description:
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
	while (all->env[++i])
	{
		if (ft_strchr(all->env[i], '='))
		{
			write(STDOUT_FILENO, all->env[i], ft_strlen(all->env[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}
