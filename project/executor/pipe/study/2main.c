#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av, char *envp[])
{
    int pipefd[2];
    char    *ls[2];
    char    *cat[2];

    ls[0] = "/usr/bin/ls";//ls и все что угодно
    ls[1] = 0;
    cat[0] = "/usr/bin/cat";
    cat[1] = 0;
    (void)ac;
    (void)av;
    pipe(pipefd);

    if (!fork())
    {
        dup2(pipefd[1],1);
        close(pipefd[1]);
        close(pipefd[0]);
        execve(ls[0], ls, envp);
    }


    if (!fork())
    {
        dup2(pipefd[1],1);
        close(pipefd[1]);
        close(pipefd[0]);
        execve(cat[0], cat, envp);
    }
    close(pipefd[0]);
    close(pipefd[1]);

    wait(0);
    wait(0);
    wait(0);

//    printf("Hello, World!\n");
    return 0;
}

// gcc -o test main.c