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

int pipe_23(char **com_name, int fd0, char **envp, int end_flag, t_command *tmp)
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
//if (end_flag&START_PIPE && end_flag&PIPE)// чтобы не менять объявл функ
//    return (0);
    return (0);
}

int     all_pipes(t_all *all, t_command *tmp, char **envp)
{
//    t_command *tmp;
//    tmp = *commands;
write(1, "pipe\n", 5);
    int stdout; int stdoutt = dup(tmp->output_fd);

//int stdout; stdout = dup(1);
    all->tmp = *all->commands;

    all->fd0 = all->tmp->input_fd;
    while (all->tmp->next && all->tmp->end_flag&PIPE)
    {
printf("tmp->args[0] = |%s|\n", all->tmp->args[0]);
stdout = stdoutt;
        all->fd0 = pipe_23(all->tmp->args, all->fd0, envp, all->tmp->end_flag, all->tmp);
        all->tmp = all->tmp->next;
    }
printf("tmp->args[0] = |%s|\n", all->tmp->args[0]);

    if (!fork())                                        // executor();
    {
        dup2(all->fd0, all->tmp->input_fd);                       // всё, что читалось бы из терминала, теперь читается из того места, куда записалось file_pipes[1] (то есть 1 после dup2)
        close(all->fd0);

//        dup2(stdout, 1);
//        close(stdout);

        execve(all->tmp->args[0], all->tmp->args, envp);          // cat теперь должен получить мою строку "123" и вывести в терминал
        exit (0);
    }
    close(all->fd0);
    wait(NULL);

    write(1, "pipe\n", 5);

    return (0);
}
