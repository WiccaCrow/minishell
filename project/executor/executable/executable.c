#include "../../includes/minishell.h"//"minishell.h"

#include <sys/types.h>//DIR *opendir(const char *name);
#include <dirent.h>//DIR *opendir(const char *name);

/************************************
 * 			1. executable			*
 * **********************************
*/
/* Description:
 * 		Function do search and do launch the right 
 * 		executable (based on the PATH variable or by 
 * 		using relative or absolute path).
 * Return value:
 * 		The function returns 1 if the name of the 
 * 		executable file was entered (with an absolute, 
 * 		relative path, or the file lies in one of the 
 * 		paths in env-variable PATH) or a path was specified.
 * 		Otherwise, 0 will be returned.
 * Variables description, code comments:
 * 		1. pointer to struct t_all all with variables:
 * 			all->completion_code;
 * 			all->env. Env-variables array (for PATH);
 * 			all->line. Input line with executable.
 * 		2. function variables:
 * 			path_from_env. Path for the executable file.
 * 			i. Iterator for path.
 * 			path. Flag. Can be 1 or 0.
 * 				path = path_to_executable(all). If 0 - 
 * 					the file is running.
 * 					if 1 and all->completion_code not zero,
 * 						it was not command.
 * 				path = find_file_in_dir(); Seach file in 
 * 					path from env-variable PATH. If 0 - 
 * 					the file is running. if P is not equal 
 * 					to 0, then the entered line is neither 
 * 					a command nor an executable file.
 * 			com_name. Command name or executable name.
 * Contains functions:
 * 		1.1. path_to_executable;
 * 		1.2. path_env;
 * 		1.3. command_name;
 * 		1.4. find_file_in_dir;
*/

int	executable(t_all *all)
{
	char	**path_from_env;
	int		i;
	int		path;
	char	*com_name;

	all->completion_code = 0;
	path = path_to_executable(all);
	if (path && all->completion_code)
		return (0);
	if (!path)
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

/************************************
 * 		1.1. path_to_executable		*
 * **********************************
*/
/* Description:
 * 		The function checks if the path contains the 
 * 		entered string (checks for the / character).
 * 		If the string consists entirely of a path, 
 * 		the message "is a directory" is displayed.
 * 		If the path in the string is found and not the 
 * 		entire string is a directory (are there characters 
 * 		after the last '/'), the function tries to follow 
 * 		the specified path. 
 * 		If the path does not exist or there is no file 
 * 		with the specified name at the end of the path, 
 * 		the message "No such file or directory" is displayed.
 * 		If the path is specified, it was possible to follow 
 * 		it, the function tries to start the executable file.
 * Return value:
 * 		1 if executable was find and running.
 * 		In other cases 0.
 * Contains functions:
 * 		1.1.1. check_command_sourse;
 * 		1.1.2. find_file;
 * 		1.3. command_name;
 * 		libft. ft_strlen;
*/

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
		else
			return (0);
	}
	return (1);
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