#include "../includes/minishell.h"

void	test_print_pwd(t_all *all);
int	change_pwd_oldpwd(t_all *all);

int	exec_cd(t_all *all)
{
	int		ret_chdir;
	int		i;

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
// если pwd нет в env, необходимо его создать
			i = change_pwd_oldpwd(all);
			all->pwd = getcwd(NULL, 0);
			if (i > 0)
				all->env[i] = ft_strjoin("PWD=", all->pwd);
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


int	change_pwd_oldpwd(t_all *all)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (all->env[i] && !(all->env[i][0] == 'P' && all->env[i][1] == 'W' && all->env[i][2] == 'D'))
		++i;
	while (all->env[j] && !(all->env[j][0] == 'O' && all->env[j][1] == 'L' && all->env[j][2] == 'D' &&
					all->env[j][3] == 'P' && all->env[j][4] == 'W' && all->env[j][5] == 'D'))
		++j;
	all->oldpwd = all->pwd;
	if (all->env[j])
	{
		free(all->env[j]);
		all->env[j] = NULL;
		all->env[j] = ft_strjoin("OLD", all->pwd);
	}
	if (all->pwd)
		all->pwd = NULL;
	if (all->env[i])
	{
		free(all->env[i]);
		all->env[i] = NULL;
		return (i);
	}
	return (-1);
}