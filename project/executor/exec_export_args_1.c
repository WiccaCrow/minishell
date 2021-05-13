#include "../includes/minishell.h"

void	subjoin_env(t_all *all, int i, int j)
{
	char **env_new;

	while (all->args[++j])
		++i;
	env_new = (char **)malloc((i + 1) * sizeof(char *));
	env_new[i] = NULL;
	while (--j >= 0)
		env_new[--i] = ft_strdup(all->args[j]);/////////////////////
	while (--i >= 0)
		env_new[i] = all->env[i];
	free(all->env);
	all->env = env_new;
}