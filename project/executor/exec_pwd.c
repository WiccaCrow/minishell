#include "../includes/minishell.h"

void	exec_pwd(t_all *all)
{
		write(STDOUT_FILENO, all->pwd, ft_strlen(all->pwd));
		write(STDOUT_FILENO, "\n", 1);
}