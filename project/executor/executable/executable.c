#include "../../includes/minishell.h"//"minishell.h"

#include <sys/types.h>//DIR *opendir(const char *name);
#include <dirent.h>//DIR *opendir(const char *name);

int	path_to_executable(t_all *all);
char *command_name(t_all *all);
int	find_file(t_all *all, char *com_name);
int		fork_execve(t_all *all, char *com_name);

int	executable(t_all *all)
{
	// char	**path;//путь для исполняемого файла
	int		i;//итератор для path
	// int		ret;//значение возврата от fork
	int		path;//указан ли путь до файла

	i = 0;
	all->completion_code = 0;
	path = path_to_executable(all);//путь до файла
	// if (!path && !all->completion_code)//если файл задан без пути, прохожусь по PATH
	// {
	// 	path = path_env(all);
	// 	ret = -1;
	// 	while (ret == -1 && path[i])//пока выполнение процесса не произошло, пробую запустить с разных путей (перенести внутрь форка на возврат от execve)
	// 	{
	// 		ret = fork_executable(all);
	// 		++i;
	// 	}
	// }

	if (all)
		return (0);
	return (0);
}

char *command_name(t_all *all)
{
	int	i;
	char *com_name;

	i = 0;
	while (all->line[i] && all->line[i] != ' ')
		++i;
	com_name = (char*)malloc(sizeof(char) * (i + 1));
	com_name[i] = '\0';
	while (i--)
		com_name[i] = all->line[i];
	return (com_name);
}

// int	fork_executable(t_all *all)
// {
// 	int	ret;

// 	  pid_t pid;
//   int rv;
//   switch(pid=fork()) {
//   case -1:
//           perror("fork"); /* произошла ошибка */
//           exit(1); /*выход из родительского процесса*/
//   case 0:
//           printf(" CHILD: Это процесс-потомок!\n");
//           printf(" CHILD: Мой PID -- %d\n", getpid());
//           printf(" CHILD: PID моего родителя -- %d\n",
//               getppid());
//           printf(" CHILD: Введите мой код возврата (как можно меньше):");
//           scanf(" %d");
//           printf(" CHILD: Выход!\n");
//           exit(rv);
//   default:
//           printf("PARENT: Это процесс-родитель!\n");
//           printf("PARENT: Мой PID -- %d\n", getpid());
//           printf("PARENT: PID моего потомка %d\n",pid);
//           printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
//         wait(pid);
//           printf("PARENT: Код возврата потомка:%d\n",
//                    WEXITSTATUS(rv));
//           printf("PARENT: Выход!\n");
//   }
// 	return (ret);
// }

int	path_to_executable(t_all *all)
{
	// char	**path;
	// int		i;
	char	*com_name;
	DIR 	*does_dir;

	com_name = command_name(all);
	does_dir = opendir(com_name);
	if (does_dir)
	{
		write(STDOUT_FILENO, "minishell: ", 12);
		write(STDOUT_FILENO, com_name, ft_strlen(com_name));
		write(STDOUT_FILENO, ": is a directory\n", 18);
		closedir(does_dir);
		all->completion_code = 126;
		return (0);
	}
	else
	{
		if (find_file(all, com_name))
		{
			write(STDOUT_FILENO, "minishell: ", 12);
			write(STDOUT_FILENO, com_name, ft_strlen(com_name));
			write(STDOUT_FILENO, ": No such file or directory\n", 29);
			all->completion_code = 126;
			return (0);
		}
	}
	return (0);
}

int	find_file(t_all *all, char *com_name)
{
	char			c;
	int				i;
	DIR 			*does_dir;
	struct dirent	*entry;
	int				cmp;

	i = ft_strlen(com_name);
	while (i && com_name[i] != '/')
		--i;
	if (com_name[i] == '/')
	{
		c = com_name[i + 1];
		com_name[i + 1] = '\0';
		does_dir = opendir(com_name);
		com_name[i + 1] = c;
		if (!does_dir)
			return (all->completion_code = 126);
		entry = readdir(does_dir);
		cmp = 1;
			//найти файл
    	while (cmp && entry != NULL)
		{
			cmp = ft_strncmp(entry->d_name, &(com_name[i + 1]), ft_strlen(&(com_name[i + 1])));

			if (cmp)
				entry = readdir(does_dir);
   		}
	// попробовать файл открыть fork execve
		if (!cmp)
			fork_execve(all, com_name);
		closedir(does_dir);
	}
	return (0);
}

int		fork_execve(t_all *all, char *com_name)
{
	printf("\n");
	int		ret;
	pid_t	pid;
//   int rv;
printf("lalala  %s\n", com_name);
	pid = fork();
	if (pid == 0)
	{
		ret = execve(com_name, all->args, all->env);
		if (ret == -1)
		{
			exit(1);
		}
	}
	else
	{
		printf("pid %d\n", pid);
		write(STDOUT_FILENO, "minishell: fork error. try again\n", 34);
		all->completion_code = 1;
		exit (1);
	}
	// wait(&pid);
	wait(NULL);
	return (0);


//   switch(pid=fork()) {
//   case -1:
//           perror("fork"); /* произошла ошибка */
//           exit(1); /*выход из родительского процесса*/
//   case 0:
//           printf(" CHILD: Это процесс-потомок!\n");
//           printf(" CHILD: Мой PID -- %d\n", getpid());
//           printf(" CHILD: PID моего родителя -- %d\n",
//               getppid());
//           printf(" CHILD: Введите мой код возврата (как можно меньше):");
//           scanf(" %d");
//           printf(" CHILD: Выход!\n");
//           exit(rv);
//   default:
//           printf("PARENT: Это процесс-родитель!\n");
//           printf("PARENT: Мой PID -- %d\n", getpid());
//           printf("PARENT: PID моего потомка %d\n",pid);
//           printf("PARENT: Я жду, пока потомок не вызовет exit()...\n");
//         wait(pid);
//           printf("PARENT: Код возврата потомка:%d\n",
//                    WEXITSTATUS(rv));
//           printf("PARENT: Выход!\n");
//   }
}