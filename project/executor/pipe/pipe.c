#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int	pipe_23(t_all *all, char **com_name, int fd0, char **envp, int end_flag, t_command *tmp)
{
	if (end_flag&PIPE)
		return (pipe_1st_midle(com_name, fd0, envp, end_flag, tmp));
	else
		return (pipe_last(all, com_name, envp, tmp));	
}

int pipe_last(t_all *all, char **com_name, char **envp, t_command *tmp)
{
    if (!fork())                                        // executor();
    {
        dup2(all->fd0, tmp->input_fd);                       // всё, что читалось бы из терминала, теперь читается из того места, куда записалось file_pipes[1] (то есть 1 после dup2)
        close(all->fd0);
        execve(com_name[0], com_name, envp);          // cat теперь должен получить мою строку "123" и вывести в терминал
        exit (0);
    }
    close(all->fd0);
    wait(NULL);
	return (0);
}

int pipe_1st_midle(char **com_name, int fd0, char **envp, int end_flag, t_command *tmp)
{
    int file_pipes[2];

    if (pipe(file_pipes) == 0)
    {
        if (!fork())
        {
            dup2(file_pipes[1], 1);                         // всё, что писалось бы в терминал, теперь пишется в то место, куда записалось file_pipes[1] (то есть после dup2)
            close(file_pipes[1]);
            close(file_pipes[0]);

            if (end_flag&START_PIPE && end_flag&PIPE)
            {
                dup2(fd0, tmp->input_fd);
                close(fd0);
            }

            execve(com_name[0], com_name, envp);            // ls теперь записан в 1
            exit (0);
        }

        if (end_flag&START_PIPE && end_flag&PIPE)
            close(fd0);
        close(file_pipes[1]);
        wait(NULL);
//        all->fd0 = file_pipes[0];
        return (file_pipes[0]);
    }
    return (0);
}

int     all_pipes(t_all *all, t_command *tmp)
{
    // int stdout; int stdoutt = dup(tmp->output_fd);

//int stdout; stdout = dup(1);
    all->tmp = tmp;

    all->fd0 = all->tmp->input_fd;
    while (all->tmp->next && all->tmp->end_flag&PIPE)
    {
printf("tmp->args[0] = |%s|\n", all->tmp->args[0]);
// stdout = stdoutt;
        executor(all, all->tmp);
        all->tmp = all->tmp->next;
    }
	if (all->tmp && all->tmp->end_flag&START_PIPE)
		executor(all, all->tmp);
    return (0);
}
