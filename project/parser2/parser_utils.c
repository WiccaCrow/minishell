#include "minishell.h"

int	set_start_pipes(t_all *all)
{
	t_command	*tmp;
	int			pipe_flag;

	pipe_flag = 0;
	if (all && all->commands)
	{
		tmp = *(all->commands);
		while (tmp)
		{
			if (pipe_flag)
				tmp->end_flag = tmp->end_flag | START_PIPE;
			pipe_flag = tmp->end_flag & PIPE;
			tmp = tmp->next;
		}
	}
	return (0);
}


int	show_commands(t_command **commands)
{
	t_command	*tmp;
	int			i;

	if (commands)
	{
		tmp = *commands;
		while (tmp)
		{
			write(STDOUT_FILENO, CURSIVE, 8);
			printf("command flag = %d\n", tmp->flag_command);
			printf("redirect flag = %d\n", tmp->redirect_type);
			printf("input fd = %d\n", tmp->input_fd);
			printf("output fd = %d\n", tmp->output_fd);
			printf("end flag = %d\n", tmp->end_flag);
			i = -1;
			if (tmp->args)
			{
				while (tmp->args[++i])
					printf("arg %d:\"%s\"\n", i, tmp->args[i]);
			}
			write(STDOUT_FILENO, NONECOLOR, 4);
			tmp = tmp->next;
		}
	}
	return (0);
}