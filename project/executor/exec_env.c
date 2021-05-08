#include "../includes/minishell.h"

void	exec_env(t_all *all)
{
	int	i;

	i = -1;
	while (all->env[++i])
	{
		write(STDOUT_FILENO, all->env[i], ft_strlen(all->env[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
