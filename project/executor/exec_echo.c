#include "minishell.h"

/************************************
 * 		1.4.2.1. echo_check_flag_n	*
 * **********************************
*/
/* Description:
 * check flag '-n'.
*/

void	echo_check_flag_n(t_command *tmp, int *i, int *flag_n)
{
	int	iter;

	*i = 0;
	*flag_n = 1;
	if ((tmp->args[*i] && tmp->args[*i][0]
		&& tmp->args[*i][1])
		&& (tmp->args[*i][0] == '-'
		&& tmp->args[*i][1] == 'n'))
	{
		iter = 1;
		while (tmp->args[*i][++iter] == 'n')
			;
		if (!tmp->args[*i][iter])
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

int	exec_echo(t_command *tmp)
{
	int	i;
	int	ret;
	int	flag_n;

	g_completion_code = 0;
	ret = 0;
	echo_check_flag_n(tmp, &i, &flag_n);
	while (tmp->args[i])
	{
		ret += write(tmp->output_fd, tmp->args[i],
				ft_strlen(tmp->args[i]));
		if (tmp->args[++i])
			ret += write(tmp->output_fd, " ", 1);
	}
	if (flag_n)
		ret += write(tmp->output_fd, "\n", 1);
//	if (tmp->output_fd != 1)
//		close(tmp->output_fd);
	return (ret > 0);
}
