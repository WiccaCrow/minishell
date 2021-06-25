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
	while (all->args[i])
	{
		printf("output_fd = %d\n", (*(all->commands))->output_fd);
		ret += write((*(all->commands))->output_fd, all->args[i], ft_strlen(all->args[i]));
		// ret += write(STDOUT_FILENO, all->args[i], ft_strlen(all->args[i]));
		if (all->args[++i])
			ret += write((*(all->commands))->output_fd, " ", 1);
			// ret += write(STDOUT_FILENO, " ", 1);
	}
	if (flag_n)
		ret += write((*(all->commands))->output_fd, "\n", 1);
		// ret += write(STDOUT_FILENO, "\n", 1);
	if ((*(all->commands))->output_fd != 1)
		close((*(all->commands))->output_fd);
	return (ret > 0);
}
