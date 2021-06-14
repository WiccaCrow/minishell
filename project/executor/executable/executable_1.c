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
 * 		1.3. find_file_in_dir;
*/

int	executable(t_all *all)
{
	char	**path_from_env;
	int		i;
	int		path;
	// char	*com_name;

	all->completion_code = 0;
	path = path_to_executable(all);
	if (path && all->completion_code == 127)
		return (1);
	if (!path || (path && all->completion_code))
		return (0);
	path_from_env = path_env(all);
	if (path_from_env == NULL)
		return (1);
	i = 0;
	path = 0;
	while (path_from_env[i] && path == 0)
		path = find_file_in_dir(all, path_from_env[i++], all->args[0], NULL);
	return (!path);
}

/************************************
 * 		1.1. path_to_executable		*
 * **********************************
*/
/* Description:
 * 		The function checks if the path contains the 
 * 		entered string (checks for the '/' character).
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
 * 		1.1.2. executable_error_print;
 * 		1.1.3. find_file;
 * 		libft. ft_strlen;
*/

int	path_to_executable(t_all *all)
{
	DIR 	*does_dir;

	if (check_command_sourse(all, all->args[0]))
		return (1);
	does_dir = opendir(all->args[0]);
	if (does_dir)
	{
		closedir(does_dir);
		return (executable_error_print(&all->completion_code, all->args[0], ": is a directory\n", 126));
	}
	else
	{
		if (find_file(all, all->args[0]))
			return (executable_error_print(&all->completion_code, all->args[0], ": No such file or directory\n", 126));
		else
			return (0);
	}
	return (1);
}

/************************************
 * 			1.3. find_file_in_dir		*
 * **********************************
*/
/* Description:
 * 		
 * Return value:
 * 		
*/

int	find_file_in_dir(t_all *all, char *directory, char *com_name, char *tmp_com_name)
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
		cmp = ft_strncmp(entry->d_name, com_name, ft_strlen(com_name));
		if (!cmp && entry->d_name[ft_strlen(com_name)])
			cmp = 1;			
		if (cmp)
			entry = readdir(does_dir);
   	}
	// попробовать файл открыть fork execve
	if (!cmp)
	{
		if (!tmp_com_name)
		{
			com_name = join_directory_and_command(directory, com_name);
			completion_code_malloc_error(&all->completion_code, com_name, all->args[0]);
			fork_execve(all, com_name);
		}
		else
			fork_execve(all, all->args[0]);
	}
	closedir(does_dir);
	if (!cmp && !tmp_com_name)
		return (1);
	if (cmp && tmp_com_name)
		return (1);
	return (0);
}
