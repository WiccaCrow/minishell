#include "minishell.h"

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
	int	i;

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

void	exec_exit(t_all *all, t_command *tmp)
{
	int	pipe_on_of;

	pipe_on_of = 0;
	if (tmp->end_flag & PIPE)
		pipe_on_of = 1;
	else
		write(tmp->output_fd, "exit\n", 5);
	g_completion_code = exit_code(all, tmp);
	if (((tmp->args[0] && !tmp->args[1]) || !tmp->args[0]) && !pipe_on_of)
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

int	exit_code(t_all *all, t_command *tmp)
{
	int	code;
	int	i;

	if (tmp->args[0] == NULL)
		return (0);
	i = -1;
	if (args_is_digit(tmp->args[0]))
	{
		write(tmp->output_fd, "bash: exit: ", 13);
		write(tmp->output_fd, tmp->args[0], ft_strlen(tmp->args[0]));
		write(tmp->output_fd, ": numeric argument required\n", 29);
		g_completion_code = 255;
		exit_clean(all);
	}
	if (tmp->args[1] != NULL)
	{
		write(tmp->output_fd, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	code = ft_atoi(tmp->args[0]);
	if (code < 0)
		return (code + 256);
	else if (code > 255)
		return (code - 256);
	return (code);
}
