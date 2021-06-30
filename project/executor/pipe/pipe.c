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

int pipe_23(char **com_name, int fd0, char **envp, int end_flag, t_command **commands)
{
    int			file_pipes[2];
	t_command	*tmp;

	if(!commands)
		return (0);
	tmp = *commands;
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
        return (file_pipes[0]);
    }
//if (end_flag&START_PIPE && end_flag&PIPE)// чтобы не менять объявл функ
//    return (0);
    return (0);
}

int     all_pipes(t_command **commands, char **envp)
{
    t_command	*tmp;
    
    if (!commands)
		return (0);
    tmp = *commands;
	write(1, "pipe\n", 5);
    int stdout;
    int stdoutt = dup(tmp->output_fd);

//int stdout; stdout = dup(1);

    int fd0;

    fd0 = tmp->input_fd;
    while (tmp->next && tmp->end_flag & PIPE)
    {
		printf("tmp->args[0] = |%s|\n", tmp->args[0]);
		stdout = stdoutt;
        fd0 = pipe_23(tmp->args, fd0, envp, tmp->end_flag, commands);
        tmp = tmp->next;
    }
    printf("tmp->args[0] = |%s|\n", tmp->args[0]);

    if (!fork())                                        // executor();
    {
        dup2(fd0, tmp->input_fd);                                   // всё, что читалось бы из терминала, теперь читается из того места, куда записалось file_pipes[1] (то есть 1 после dup2)
        close(fd0);

//        dup2(stdout, 1);
//        close(stdout);

        execve(tmp->args[0], tmp->args, envp);          // cat теперь должен получить мою строку "123" и вывести в терминал
        exit (0);
    }
    close(fd0);
    wait(NULL);

    write(1, "pipe\n", 5);

    return (0);
}
