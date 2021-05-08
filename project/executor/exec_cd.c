#include "../includes/minishell.h"

void	test_print_pwd(t_all *all);

int	exec_cd(t_all *all)
{
	int		ret_chdir;
	int		i;
	char	*cur_dir;

// test_print_pwd(all);
	ret_chdir = 0;
	i = 0;
	if (all->args[0] == NULL)
		return (0);
	ret_chdir = chdir(all->args[0]);

	if (ret_chdir == -1)
	{
		write(STDERR_FILENO, "minishell: cd: ", 16);
		char *err = strerror(errno);
		write(STDERR_FILENO, err, ft_strlen(err));
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
		while (all->env[i] && !(all->env[i][0] == 'P' && all->env[i][1] == 'W' && all->env[i][2] == 'D'))
			++i;
// если pwd нет в env, необходимо его создать
		if (all->env[i] != NULL)
		{
			if (all->pwd)
			{
				free(all->pwd);
				all->pwd = NULL;
			}
			cur_dir = getcwd(NULL, 0);
			all->pwd = ft_strjoin("PWD=", cur_dir);
			free(all->env[i]);
			all->env[i] = NULL;
			all->env[i] = ft_strdup(all->pwd);
			free(cur_dir);
			cur_dir = NULL;
		}
	}
// test_print_pwd(all);
	return (ret_chdir);
}

void	test_print_pwd(t_all *all)
{
	int i;
	
	i = 0;
	while (all->env[i])
	{
		if (all->env[i][0] == 'P' && all->env[i][1] == 'W' && all->env[i][2] == 'D')
			break ;
		++i;
	}
	write(1, all->env[i], ft_strlen(all->env[i]));
	write(1, "\n", 1);
}
