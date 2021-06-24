#include "../../includes/minishell.h"//"minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int pipe_execve(t_all *all, char *filename_with_path)
{

    if ((*(all->commands))->end_flag & PIPE)
        return (pipe(all, filename_with_path));
    else
        return (fork_execve(all, filename_with_path));
}

int pipe(t_all *all, char *filename_with_path)
{
    int     pipe_1[2];
    int     pipe_2[2];

    pipe(pipe_1);
    if (!fork())
    {
       if ((*(all->commands))->end_flag&PIPE)
       {
           dup2(pipe_2[0], 0);
           close(pipe_2[1]);
           close(pipe_2[0]);
       }
       if (((*(all->commands))->start_flag&PIPE)
       {
           dup2(pipe_1[1], 0);
           close(pipe_1[1]);
           close(pipe_1[0]);
       }
       execve(filename_with_path, all->args, all->env);
    }
    if ((*(all->commands))->start_flag&PIPE)
        close(pipe_1[1]);
    if ((*(all->commands))->end_flag&PIPE)
        close(pipe_2[0]);

    /*

    char    *ls[2];
    char    *head[2];
    char    *wc[2];

    ls[0] = "/usr/bin/ls";
    ls[1] = 0;
    head[0] = "/usr/bin/head";
    head[1] = 0;
    wc[0] = "/usr/bin/wc";
    wc[1] = 0;
    (void)ac;
    (void)av;
    pipe(pipe_1);
    if (!fork())
    {
        dup2(pipe_1[0],0);
        close(pipe_1[1]);
        close(pipe_1[0]);
        execve(ls[0], ls, envp);
    }
    close(pipe_1[0]);
    printf("Hello, World!\n");
     */
    return 0;
}