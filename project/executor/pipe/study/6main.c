#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct			s_command {
    char 				**args; // аргументы комманды
    int					end_flag;
    int					input_fd;
    int					output_fd;
    int					redirect_type;
    int					return_code; // код возврата ошибки $?
    struct s_command	*next;
}						t_command;

int pipe_23(char **com_name, int fd0, char **envp)
{
    int file_pipes[2];

    pipe(file_pipes);
    if (!fork())
    {
        dup2(file_pipes[1], 1);                         // всё, что писалось бы в терминал,
                                                        // теперь пишется в то место, куда
                                                        // записалось file_pipes[1] (то есть 0
                                                        // после dup2)
        close(file_pipes[1]);
        close(file_pipes[0]);

        dup2(fd0, 0);
        close(fd0);
        execve(com_name[0], com_name, envp);            // ls теперь записан в 1
    }
    close(fd0);
    close(file_pipes[1]);
    return (file_pipes[0]);
}

int all_pipes(t_command **commands, char **envp)
{
    t_command *tmp;
    tmp = *commands;

    int file_pipes[2];

    int fd0;

    if (pipe(file_pipes) == 0)                              // создаю канал
    {
        if (!fork())
        {
            dup2(file_pipes[1], 1);                         // всё, что писалось бы в терминал,
                                                            // теперь пишется в то место, куда
                                                            // записалось file_pipes[1] (то есть 0
                                                            // после dup2)
            close(file_pipes[1]);
            close(file_pipes[0]);
            execve(tmp->args[0], tmp->args, envp);          // ls теперь записан в 1
        }
        close(file_pipes[1]);
        fd0 = file_pipes[0];
        tmp = tmp->next;

        if (tmp->end_flag == 2)
        {

            fd0 = pipe_23(tmp->args, file_pipes[0], envp);
            tmp = tmp->next;
        }

        if (!fork())                                        //executor();
        {
            dup2(fd0, 0);                                   // всё, что читалось бы из терминала,
                                                            // теперь читается из того места, куда
                                                            // записалось file_pipes[1] (то есть 1
                                                            // после dup2)
            close(fd0);
            execve(tmp->args[0], tmp->args, envp);          // cat теперь должен получить мою
                                                            // строку "123" и вывести в терминал
        }
        close(fd0);
//        printf("tmp->args[0] = %s\n", tmp->args[0]);

        wait(NULL);
        wait(NULL);
        wait(NULL);
    }
    return (0);
}

int    fill_commands(t_command **commands)
{
    int i = 4;
    t_command *tmp;

    //com1
    *commands = (t_command *)malloc(sizeof(t_command));
    tmp = *commands;
    tmp->args = (char **)malloc(sizeof(char*) * 3);
    tmp->args[0] = "/bin/ls";//ls и все что угодно;
    tmp->args[1] = 0;
    tmp->args[2] = NULL;
    tmp->end_flag = 1;// справа пайп

    //com2
    tmp->next = (t_command *)malloc(sizeof(t_command));
    tmp = tmp->next;
    tmp->args = (char **)malloc(sizeof(char*) * 4);
    tmp->args[0] = "/bin/cat";//ls и все что угодно;
    tmp->args[1] = "-e";
    tmp->args[2] = 0;
    tmp->args[3] = NULL;
    tmp->end_flag = 2;// слева и справа пайп

    //com3
    tmp->next = (t_command *)malloc(sizeof(t_command));
    tmp = tmp->next;
    tmp->args = (char **)malloc(sizeof(char*) * 4);
    tmp->args[0] = "/usr/bin/wc";//ls и все что угодно;
    tmp->args[1] = 0;
    tmp->args[2] = 0;
    tmp->args[3] = NULL;
    tmp->end_flag = 3;// слева пайп
    tmp->next = NULL;

    return (0);
}

int main(int ac, char *av[], char **envp)
{
    t_command   **commands;

    commands = (t_command **)calloc(1, sizeof (t_command *));
//write(1, "test 1\n", 7);
    fill_commands(commands);
//write(1, "test 2\n", 7);
    all_pipes(commands, envp);
//write(1, "test 3\n", 7);

    return (0);
}

