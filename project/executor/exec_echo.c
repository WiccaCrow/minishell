#include "../includes/minishell.h"

/************************************
 * 		1.4.2.1. echo_check_flag_n	*
 * **********************************
*/
/* Description:
 * check flag '-n'.
*/

void	echo_check_flag_n(t_all *all, int *i, int *flag_n)
{
	int	iter;

	*i = 0;
	*flag_n = 1;
	if (((*all->commands)->args[*i] && (*all->commands)->args[*i][0] && (*all->commands)->args[*i][1])
		&& ((*all->commands)->args[*i][0] == '-' && (*all->commands)->args[*i][1] == 'n'))
	{
		iter = 1;
		while ((*all->commands)->args[*i][++iter] == 'n')
			;
		if (!(*all->commands)->args[*i][iter])
		{
			*i = 1;
			*flag_n = 0;
		}
	}
}

/************************************
 * 		1.4.2. exec_echo			*
 * **********************************
*/
/* Description:
 * execution command 'echo'.
 * 
 * function:
 * 1.4.2.1. echo_check_flag_n;
 * 			check flag '-n'.
 * libft. ft_strlen.
*/

int exec_echo(t_all *all)
{
	int i;
	int ret;
	int	flag_n;

    g_completion_code = 0;
	ret = 0;
	echo_check_flag_n(all, &i, &flag_n);
	while ((*all->commands)->args[i])
	{
		printf("output_fd = %d\n", (*all->commands)->output_fd);
		ret += write((*all->commands)->output_fd, (*all->commands)->args[i], ft_strlen((*all->commands)->args[i]));
		// ret += write(STDOUT_FILENO, (*all->commands)->args[i], ft_strlen((*all->commands)->args[i]));
		if ((*all->commands)->args[++i])
			ret += write((*all->commands)->output_fd, " ", 1);
			// ret += write(STDOUT_FILENO, " ", 1);
	}
	if (flag_n)
		ret += write((*all->commands)->output_fd, "\n", 1);
		// ret += write(STDOUT_FILENO, "\n", 1);
	if ((*all->commands)->output_fd != 1)
		close((*all->commands)->output_fd);
	return (ret > 0);
}
