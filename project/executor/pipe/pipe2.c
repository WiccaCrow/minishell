#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//int execve_pipe(t_all *all, char *filename_with_path)
//{
//    if ((*all->commands)->end_flag&START_PIPE || (*all->commands)->end_flag&PIPE)
//        all_pipes(all->commands, all->env);
//    else
//        return (fork_execve(all, filename_with_path));
//    return (0);
//}

/**
 * 
 * изменил функцию, теперь она принимает конкретную команду, а не лист
 * возвращает выходной конец трубы
 */

int pipe_23(char **com_name, int fd0, char **envp, int end_flag, t_command *command)
{
    int			file_pipes[2];

	(void) end_flag;
	if(!command)
		return (0);
    if (pipe(file_pipes) == 0)
	{
		if (!fork())
		{
			dup2(file_pipes[1], 1);  // всё, что писалось бы в терминал, 
			// теперь пишется в то место, куда записалось file_pipes[1] (то есть после dup2)
			close(file_pipes[1]);
			dup2(fd0, 0);
			close(fd0);
			execve(com_name[0], com_name, envp); // ls теперь записан в 1
			exit(0);
		}
		wait(NULL);
		return (file_pipes[0]);
	}
    return (0);
}

int     all_pipes(t_command **commands, char **envp)
{
    t_command	*tmp;
    int			input_fd;
    
    if (commands)
	{
		tmp = *commands;
		input_fd = tmp->input_fd;
		write(1, "pipe\n", 5);
		while (tmp)
		{
			if (tmp->end_flag & PIPE)
			{
				input_fd = pipe_23(tmp->args, input_fd, envp, tmp->end_flag,
								   tmp);
			}
			printf("tmp->args[0] = |%s|\n", tmp->args[0]);
			tmp = tmp->next;
		}
		write(1, "pipe\n", 5);
	}
    return (0);
}
