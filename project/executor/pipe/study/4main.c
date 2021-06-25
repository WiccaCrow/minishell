#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// проблема с cat не решена

int main(int ac, char *av[], char **envp)
{
    int file_pipes[2];

    char *com2[2];
    com2[0] = "/bin/cat";//ls и все что угодно
    com2[1] = 0;

    if (pipe(file_pipes) == 0)                              //создаю канал
    {

        if (!fork())
        {
            dup2(file_pipes[1], 1);                         // всё, что писалось бы в терминал,
                                                            // теперь пишется в то место, куда
                                                            // записалось file_pipes[1] (то есть 0
                                                            // после dup2)
            close(file_pipes[1]);
            close(file_pipes[0]);
            write(1, "test\n", 5);                              //текст "test\n" записан в то место, на
                                                                // которое указывает file_pipes[1]
        }

        if (!fork())
        {
            dup2(file_pipes[0], 0);                         // всё, что читалось бы из терминала,
                                                            // теперь читается из того места, куда
                                                            // записалось file_pipes[1] (то есть 1
                                                            // после dup2
            close(file_pipes[1]);
            close(file_pipes[0]);
            execve(com2[0], com2, envp);                    // cat теперь должен получить мою
                                                            // строку "test\n" и вывести в терминал
        }
        close(file_pipes[0]);
        close(file_pipes[1]);
        wait(NULL);
        wait(NULL);
    }
    return (0);
}
