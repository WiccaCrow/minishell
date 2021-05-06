#include "../includes/minishell.h"

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
		ret += write(STDOUT_FILENO, all->args[i], ft_strlen(all->args[i]));
		if (all->args[++i])
			ret += write(STDOUT_FILENO, " ", 1);
	}
	if (flag_n)
		ret += write(STDOUT_FILENO, "\n", 1);
	return (ret > 0);	
}
