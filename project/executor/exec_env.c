#include "../includes/minishell.h"

void	exec_env(t_all *all, char **env_my)
{
	int	i;

	i = -1;
	while (env_my[++i])
	{
		if (all->flag_command == export)
			write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
		write(STDOUT_FILENO, env_my[i], ft_strlen(env_my[i]));
		write(STDOUT_FILENO, "\n", 1);
	}
}
