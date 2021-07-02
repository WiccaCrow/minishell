#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	pipe_23(t_all *all, t_command *tmp)
{
	if (tmp->end_flag&PIPE)
		return (pipe_1st_midle(all, tmp->args, tmp->end_flag, tmp));
	else
		return (pipe_last(all, tmp->args, all->env, tmp));	
}

int pipe_last(t_all *all, char **com_name, char **envp, t_command *tmp)
{
    if (!fork())                                        // executor();
	{
		dup2(all->fd0, tmp->input_fd);                       // всё, что читалось бы из терминала, теперь читается из того места, куда записалось file_pipes[1] (то есть 1 после dup2)
		if (tmp->flag_command == 0 && g_completion_code == 0)
			execve(com_name[0], com_name, envp);          // cat теперь должен получить мою строку "123" и вывести в терминал
		else
			executor(all, tmp);
		exit (0);
	}
	close(all->fd0);
	wait(NULL);
	return (0);
}

int	pipe_1st_midle(t_all *all, char **com_name, int end_flag, t_command *tmp)
{
	int	file_pipes[2];

	if (pipe(file_pipes) == 0)
	{
		if (!fork())
		{
			dup2(file_pipes[1], tmp->output_fd);                         // всё, что писалось бы в терминал, теперь пишется в то место, куда записалось file_pipes[1] (то есть после dup2)
			close(file_pipes[0]);

			dup2(all->fd0, tmp->input_fd);
			if (tmp->flag_command == 0 && g_completion_code == 0)
				execve(com_name[0], com_name, all->env);            // ls теперь записан в 1
			else
				executor(all, tmp);
			exit (0);
		}
		if (end_flag&START_PIPE && end_flag&PIPE)
			close(all->fd0);
		close(file_pipes[1]);
		wait(NULL);
		return (file_pipes[0]);
	}
	return (0);
}

int	all_pipes(t_all *all, t_command *tmp)
{
printf("pipes\n");
	all->fd0 = tmp->input_fd;
	while (tmp->next && tmp->end_flag&PIPE)
	{
printf("tmp->args[0] = |%s|\n", tmp->args[0]);
		if (tmp->flag_command == 0)
			executor(all, tmp);
		if (tmp->flag_command || g_completion_code)
			all->fd0 = pipe_1st_midle(all, NULL, tmp->end_flag, tmp);
		tmp = tmp->next;
		g_completion_code = 0;
	}
	if (tmp && tmp->end_flag&START_PIPE)
	{
		if (tmp->flag_command == 0)
			executor(all, tmp);
		if (tmp->flag_command || g_completion_code)
			pipe_last(all, NULL, NULL, tmp);
	}
printf("pipes finish\n");
	return (0);
}
