#include "minishell.h"

/************************************
 * 				 path_env			*
 * **********************************
*/
/* Description:
 * 		The function splits the PATH-variable string 
 * 		in env-array into a two-dimensional array of 
 * 		strings when each character ':' is encountered.
 * Return value:
 * 		Two-dimensional array of path-strings.
*/

void	path_env(t_all *all)
{
	int		i;
	char	*path_env_value;

	i = get_my_env_index(all->env, "PATH", 4);
	if (all->env[i] == NULL)
	{
		all->path_split = NULL;
		return ;
	}
	path_env_value = ft_strchr(all->env[i], '=');
	all->path_split = ft_split(++path_env_value, ':');
	if (all->path_split == NULL)
	{
		g_completion_code = 1;
		write(STDERR_FILENO, "minishell: ", 12);
		write(STDERR_FILENO, (*all->commands)->args[0],
			ft_strlen((*all->commands)->args[0]));
		write(STDERR_FILENO, ": malloc error. Try again.\n", 28);
	}
}

/************************************
 * 		join_directory_and_command	*
 * **********************************
*/
/* Description:
 * 		The function join two strings (directory and 
 * 		command_name) to one new string.
 * Return value:
 * 		New strings.
*/

char	*join_directory_and_command(char *directory, char *command_name)
{
	char	*tmp;

	tmp = ft_strjoin("/", command_name);
	if (tmp)
	{
		command_name = ft_strjoin(directory, tmp);
		free(tmp);
		tmp = NULL;
	}
	else
		completion_code_malloc_error(tmp, command_name);
	return (command_name);
}

/****************************************
 * 		repointer_to_filename_with_path	*
 * **************************************
*/
/* Description:
 * 		The function replaces the *args0 line 
 * 		with the filename_with_pathline, the 
 * 		filename_with_path line is freed.
*/

void	repointer_to_filename_with_path(char **args0, char *filename_with_path)
{
	if (*args0 != filename_with_path)
	{
		free(*args0);
		*args0 = filename_with_path;
	}
}
