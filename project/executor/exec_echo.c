#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (!s1[i] && i < n)
	{
		if (!s2[i] || s2[i] != s1[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i] && !s1[i])
		return (s1[i] - s2[i]);
	return (0);
}

int	echo_find_env(t_all *all, int *i, int *j)
{
	char	dollar;
	int		jj;
	int		iter;
	int		ret;

	jj = 0;
	ret = 0;
	dollar = 0;
	while (all->args[*i][*j + jj] && all->args[*i][*j + jj] != '$')
		++jj;
	dollar = all->args[*i][*j + jj];
	if (dollar)
	{
		all->args[*i][*j + jj] = '\0';
		iter = 0;
		while (all->env[iter])
		{
			if (!ft_strcmp(all->env[iter], &all->args[*i][*j], jj))
			{
			ret += write(1, all->env[iter], ft_strlen(all->env[iter]));
				break ;
			}
			++iter;
		}
	}
	all->args[*i][*j + jj] = dollar;
	return(ret);
}

void	echo_write_args(t_all *all, int i, int *ret)
{
	int	j;
	int	start_args;

	j = 0;
	start_args = 0;
	while (all->args[i][j])
	{
		start_args = j;
		while(all->args[i][j] && all->args[i][j] != '$')
			++j;
		*ret += write(STDOUT_FILENO, &all->args[i][start_args], j);
		if (all->args[i][j] == '$' && !all->args[i][j + 1])
			*ret += write(STDOUT_FILENO, &all->args[i][j], 1);
		else if (all->args[i][j] == '$' && all->args[i][j + 1] == '?')
			all->return_code;
		else
			*ret += echo_find_env(all, &i, &j);
		j++;
	}
	*ret += echo_find_env(all, &i, &j);
	// ret += write(STDOUT_FILENO, all->args[i], ft_strlen(all->args[i]));
}

void	echo_check_flag_n(t_all *all, int *i, int *flag_n)
{
	int	iter;

	*i = 0;
	*flag_n = 1;
	if ((all->args[*i] && all->args[*i][0] && all->args[*i][1])
		&& (all->args[*i][0] == '-' && all->args[*i][1] == 'n'))
	{
		iter = 1;
		while (all->args[*i][++iter] == 'n')
			;
		if (!all->args[*i][iter])
		{
			*i = 1;
			*flag_n = 0;
		}
	}
}

int exec_echo(t_all *all)
{
	int i;
	int ret;
	int	flag_n;
	// write(1, "test exec_echo\n", 16);

	ret = 0;
	echo_check_flag_n(all, &i, &flag_n);
	while (all->args[i])
	{
		echo_write_args(all, i, &ret);
		// ret += write(STDOUT_FILENO, all->args[i], ft_strlen(all->args[i]));
		if (all->args[++i])
			ret += write(STDOUT_FILENO, " ", 1);
	}
	if (flag_n)
		ret += write(STDOUT_FILENO, "\n", 1);
	return (ret > 0);
	// добавить в историю напечатанное и отфришить весь массив all->args
}
