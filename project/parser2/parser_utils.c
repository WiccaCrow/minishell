#include "minishell.h"

int 			set_start_pipes(t_all *all)
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

