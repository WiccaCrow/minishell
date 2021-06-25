#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int execve_pipe(t_all *all, char *filename_with_path)
{
    if ((*all->commands)->end_flag&START_PIPE || (*all->commands)->end_flag&PIPE)
    {write(1, "pipe\n", 5);}
    else
        return (fork_execve(all, filename_with_path));
    return (0);
}

//int pipe(int ac, char *av[], char **envp)
//{
//    int file_pipes[2];
//
//    char *com1[2];
//    com1[0] = "/bin/ls";//ls и все что угодно
//    com1[1] = 0;
//
//    char *com2[2];
//    com2[0] = "/bin/cat";//ls и все что угодно
//    com2[1] = 0;
//
//    if (pipe(file_pipes) == 0)                              //создаю канал
//    {
//        if (!fork())
//        {
//            dup2(file_pipes[1], 1);                         // всё, что писалось бы в терминал,
//                                                            // теперь пишется в то место, куда
//                                                            // записалось file_pipes[1] (то есть 0
//                                                            // после dup2)
//            close(file_pipes[1]);
//            close(file_pipes[0]);
//            execve(com1[0], com1, envp);                    // ls теперь записан в 1
//        }
//
//        if (!fork())                                        //executor();
//        {
//            dup2(file_pipes[0], 0);                         // всё, что читалось бы из терминала,
//                                                            // теперь читается из того места, куда
//                                                            // записалось file_pipes[1] (то есть 1
//                                                            // после dup2)
//            close(file_pipes[1]);
//            close(file_pipes[0]);
//            execve(com2[0], com2, envp);                    // cat теперь должен получить мою
//                                                            // строку "123" и вывести в терминал
//        }
//        close(file_pipes[0]);
//        close(file_pipes[1]);
//        wait(NULL);
//        wait(NULL);
//    }
//    return (0);
//}
