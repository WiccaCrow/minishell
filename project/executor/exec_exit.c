#include "../includes/minishell.h"

/************************************
 * 			args_is_digit			*
 * **********************************
*/
/* Description:
 * 		Check args.	Is the args a number?
 * Return value:
 * 		0 if args a number.
*/

int	args_is_digit(char *args)
{
	int i;

	i = 0;
	if (args[i] == '+' || args[i] == '-')
		++i;
	while ((args[i] >= '0') && (args[i] <= '9'))
		++i;
	return (args[i] != '\0');
}

/************************************
 * 				exit				*
 * **********************************
*/
/* Description:
 * 		Exit with completion code.
*/

void	exec_exit(t_all *all)
{
	int	pipe_on_of;

	pipe_on_of = 0;
	if ((*(all->commands))->end_flag&PIPE)
		pipe_on_of = 1;
	write((*(all->commands))->output_fd, "exit\n", 6);
    g_completion_code = exit_code(all);
	if (((all->args[0] && !all->args[1]) || !all->args[0]) && !pipe_on_of)
		exit_clean(all);
}

/************************************
 * 				exit_code			*
 * **********************************
*/
/*
 * Description:
 * 		Set completion code.
*/

int	exit_code(t_all *all)
{
	int	code;
	int	i;

	if (all->args[0] == NULL)
		return (0);
	i = -1;
	if (args_is_digit(all->args[0]))
	{
		write((*(all->commands))->output_fd, "bash: exit: ", 13);
		write((*(all->commands))->output_fd, all->args[0], ft_strlen(all->args[0]));
		write((*(all->commands))->output_fd, ": numeric argument required\n", 29);
        g_completion_code = 255;
		exit_clean(all);
	}
	if (all->args[1]!= NULL)
	{
		write((*(all->commands))->output_fd, "minishell: exit: too many arguments\n", 37);
		return(1);
	}
	code = ft_atoi(all->args[0]);
	if (code < 0)
		return (code + 256);
	else if (code > 255)
		return (code - 256);
	return (code);
}
