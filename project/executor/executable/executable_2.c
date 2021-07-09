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
		g_completion_code = 1;
		write(STDERR_FILENO, "minishell: ", 12);
		write(STDERR_FILENO, (*all->commands)->args[0],
			ft_strlen((*all->commands)->args[0]));
		write(STDERR_FILENO, ": malloc error. Try again.\n", 28);
	}
	return (path_env);
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

/****************************************
 * 				wait_status_fork		*
 * **************************************
*/
/* Description:
 * 		The function processes the return value from the fork and fills in
 * 		the g_completion_code from WEXITSTATUS(status) or WIFSIGNALED(status), 
 * 		or WSTOPSIG(status).
*/

void	wait_status_fork(pid_t onepid)
{
	int	status;
	int	option;
	int	ex;
	int	ter;
	int	st;

	ex = 0;
	ter = 0;
	option = 0;
	waitpid(onepid, &status, option);
	ex = WIFEXITED(status);
	if (ex)
		g_completion_code = WEXITSTATUS(status);
	else
		ter = WIFSIGNALED(status);
	if (!ex && ter)
		g_completion_code = WTERMSIG(status);
	else
		st = WIFSTOPPED(status);
	if (!ex && !ter && st)
		g_completion_code = WSTOPSIG(status);
}
