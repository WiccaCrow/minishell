#include "../../includes/minishell.h"//"minishell.h"

#include <sys/types.h>//DIR *opendir(const char *name);
#include <dirent.h>//DIR *opendir(const char *name);

int	check_command_sourse(t_all *all, char *com_name);
int	path_to_executable(t_all *all);
char *command_name(t_all *all);
int	find_file(t_all *all, char *com_name);
int		fork_execve(t_all *all, char *com_name);
char	**path_env(t_all *all);
int	find_file_in_dir(t_all *all, char *directory, char *command_name);
char	*join_directory_and_command(char *directory, char *command_name);

int	executable(t_all *all)
{
	char	**path_from_env;//путь для исполняемого файла
	int		i;//итератор для path
	int		path;//указан ли путь до файла
	char	*com_name;

	all->completion_code = 0;
	path = path_to_executable(all);//путь до файла
	if (path && all->completion_code)
		return (0);
	path_from_env = path_env(all);
	if (path_from_env == NULL)
		return (1);
	com_name = command_name(all);
	i = 0;
	path = 0;
	while (path_from_env[i] && path == 0)
		path = find_file_in_dir(all, path_from_env[i++], com_name);
	return (!path);
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

int	check_command_sourse(t_all *all, char *com_name)
{
	int	i;

	i = 0;
	if (com_name[0] == '.' && com_name[1] == '\0')
	{
		write(STDOUT_FILENO, "minishell: This command is missing from the subject.\n", 54);
		write(STDOUT_FILENO, "In the shell, . is a builtin command ", 38);
		write(STDOUT_FILENO, "in its own right, an alias for 'source',", 41);
		write(STDOUT_FILENO, "which is used to read in a shell script ", 41);
		write(STDOUT_FILENO, "and execute its commands in the current ", 41);
		write(STDOUT_FILENO, "shell rather than spawning a subshell, t", 41);
		write(STDOUT_FILENO, "ypically used for scripts that set envir", 41);
		write(STDOUT_FILENO, "onment variables that you want to use later.\n", 46);
		return (all->completion_code = 1);
	}
	if (!ft_strchr(com_name, '/'))
		return (1);
	return (0);
}

int	path_to_executable(t_all *all)
{
	char	*com_name;
	DIR 	*does_dir;

	com_name = command_name(all);
	if (check_command_sourse(all, com_name))
		return (1);
	does_dir = opendir(com_name);
	if (does_dir)
	{
		write(STDOUT_FILENO, "minishell: ", 12);
		write(STDOUT_FILENO, com_name, ft_strlen(com_name));
		write(STDOUT_FILENO, ": is a directory\n", 18);
		closedir(does_dir);
		all->completion_code = 126;
		return (1);
	}
	else
	{
		if (find_file(all, com_name))
		{
			write(STDOUT_FILENO, "minishell: ", 12);
			write(STDOUT_FILENO, com_name, ft_strlen(com_name));
			write(STDOUT_FILENO, ": No such file or directory\n", 29);
			all->completion_code = 126;
			return (1);
		}
	}
	return (1);
}

int	find_file_in_dir(t_all *all, char *directory, char *command_name)
{
	DIR 			*does_dir;
	struct dirent	*entry;
	int				cmp;

	does_dir = opendir(directory);
	if (!does_dir)
		return (all->completion_code = 126);
	entry = readdir(does_dir);
	cmp = 1;
			//найти файл
    while (cmp && entry != NULL)
	{
		cmp = ft_strncmp(entry->d_name, command_name, ft_strlen(command_name));
		if (!cmp && entry->d_name[ft_strlen(command_name)])
			cmp = 1;			
		if (cmp)
			entry = readdir(does_dir);
   	}
	// попробовать файл открыть fork execve
	if (!cmp)
	{
		command_name = join_directory_and_command(directory, command_name);
		completion_code_malloc_error(&all->completion_code, command_name, all->line);
		fork_execve(all, command_name);
	}
	closedir(does_dir);
	if (!cmp)
		return (1);
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
	cmp = 0;
	if (com_name[i] == '/')
	{
		c = com_name[i + 1];
		com_name[i + 1] = '\0';
		does_dir = opendir(com_name);
		com_name[i + 1] = c;
		if (!does_dir)
			return (all->completion_code = 126);
		entry = readdir(does_dir);
		cmp = 1;// 0 файл найден, не 0 не найден файл
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
	return (cmp);
}

int		fork_execve(t_all *all, char *com_name)
{
	int		ret;
	pid_t	pid;
	int		rv;

	ret = 2;
	pid = fork();
	if (pid == 0)
	{
		ret = execve(com_name, all->args, all->env);
		if (ret == -1)
		{
			exit(rv = 2);
		}
	}
	else if (pid < 0)
	{
		printf("pid %d\n", pid);
		write(STDOUT_FILENO, "minishell: fork error. try again\n", 34);
		all->completion_code = 1;
		return (1);
	}
	// wait(&pid);
	wait(NULL);
// printf("\nfork_execve  |%s|%d|\n", com_name, WEXITSTATUS(rv));

	return (!ret);
}

char	**path_env(t_all *all)
{
	int		i;
	char	*path_env_value;
	char	**path_env;

	i = get_my_env_index(all->env, "PATH", 4);
	if (all->env[i] == NULL)
		return (NULL);
	path_env_value = ft_strchr(all->env[i], '=');
	path_env = ft_split(++path_env_value, ':');
	if (path_env == NULL)
	{
		all->completion_code = 1;
		write(STDOUT_FILENO, "minishell: ", 12);
		write(STDOUT_FILENO, all->line, ft_strlen(all->line));
		write(STDOUT_FILENO, ": malloc error. Try again.\n", 28);
	}
	return (path_env);
}

char	*join_directory_and_command(char *directory, char *command_name)
{
	char	*tmp;

	tmp = command_name;
	command_name = ft_strjoin("/", command_name);
	if (command_name)
	{
		free(tmp);
		tmp = command_name;
		command_name = ft_strjoin(directory, command_name);
		if (command_name)
			free(tmp);
	}
	return (command_name);
}