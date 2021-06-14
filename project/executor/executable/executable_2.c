#include "../../includes/minishell.h"//"minishell.h"

#include <sys/types.h>//DIR *opendir(const char *name);
#include <dirent.h>//DIR *opendir(const char *name);

/************************************
 * 	1.1.1. check_command_sourse		*
 * **********************************
*/
/* Description:
 * 		1) The function looks for the '/' character. 
 * 		2) The function checks if only the '.' 
 * 			Character has been entered.
 * 			If yes, completion code is set to 1.
 * Return value:
 * 		If the string com_name contain '/' character or
 * 		contain only '.', return 1.
 * 		else it return 0.
*/

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

/************************************
 * 	1.1.2. executable_error_print	*
 * **********************************
*/
/* Description:
 * 		Set value error_code to *code_to_on.
 * 		Print error message error_message for 
 * 		input string com_name (command, directory,
 * 		executable, etc.).
 * Return value:
 * 		Integer 1.
*/

int	executable_error_print(int	*code_to_on, char *com_name, char *error_message, int error_code)
{
	write(STDOUT_FILENO, "minishell: ", 12);
	write(STDOUT_FILENO, com_name, ft_strlen(com_name));
	write(STDOUT_FILENO, error_message, ft_strlen(error_message));
	*code_to_on = error_code;
	return (1);
}

/************************************
 * 	1.1.2. split_name_directory	*
 * **********************************
*/
/* Description:
 * 		Set value error_code to *code_to_on.
 * 		Print error message error_message for 
 * 		input string com_name (command, directory,
 * 		executable, etc.).
 * Return value:
 * 		Integer 1.
*/

int	split_name_directory(t_all *all, char **directory, char **com_name)
{
	int		i;
	int		cmp;
	char	c;

	i = ft_strlen(*com_name);
	while (i && (*com_name)[i] != '/')
		--i;
	cmp = 0;
	if ((*com_name)[i] == '/')
	{
		c = (*com_name)[i + 1];
		(*com_name)[i + 1] = '\0';
		*directory = ft_strdup((*com_name));
		(*com_name)[i + 1] = c;
		*com_name = ft_strdup(&((*com_name)[i + 1]));
		cmp = 1;
		if (*directory == NULL || *com_name == NULL)
			completion_code_malloc_error(&(all->completion_code), NULL, "executable (split_name_directory): ");
	}
	return (cmp);
}

/************************************
 * 			1.1.3. find_file		*
 * **********************************
*/
/* Description:
 * 		The function searches for the specified 
 * 		file "com_name" inside the directory, 
 * 		the path to which is specified before 
 * 		the file name.
 * 		If the file was found, the function tries 
 * 		to run it.
 * Return value:
 * 		Integer 0. If the file was found and the 
 * 		function launched it.
 * 		Else return not zero (1 or compiletion code).
*/

int	find_file(t_all *all, char *com_name)
{
	char			*directory;
	int				cmp;
	char			*tmp_com_name;

	cmp = 0;
	tmp_com_name = com_name;
	if (split_name_directory(all, &directory, &com_name))
	{
		if (!all->completion_code)
			return (find_file_in_dir(all, directory, com_name, tmp_com_name));
		else
			return (all->completion_code);
	}
	return (cmp);
}

/************************************
 * 				fork_execve			*
 * **********************************||||||||||||||||||||||||||||||||||||||||||||||||||||||||
*/

int		fork_execve(t_all *all, char *com_name)
{
	int		ret;
	pid_t	pid;
	int		rv;
printf("fork_execve test 1\n");
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

/************************************
 * 				 path_env			*
 * **********************************
*/
/* Description:
 * 		The function splits the PATH-variable string in env-array into a two-dimensional array of strings when each character PPRRP is encountered.
 * Return value:
 * 		Integer 0. If the file was found and the 
 * 		function launched it.
 * 		Else return not zero (1 or compiletion code).
*/

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