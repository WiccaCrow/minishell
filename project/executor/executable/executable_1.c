#include "minishell.h"

/************************************
 * 			1. executable			*
 * **********************************
*/
/* Description:
 * 		Function do search and do launch the right executable (based on the
 * 		PATH variable or by using relative or absolute path).
 * Return value:
 * 		The function returns 1 if the name of the executable file was entered
 * 		(with an absolute, relative path, or the file lies in one of the paths
 * 		in env-variable PATH) or a path was specified.
 * 		Otherwise, 0 will be returned.
 * Variables description, code comments:
 * 		1. pointer to struct t_all all with variables:
 * 			all->env. Env-variables array (for PATH);
 * 			(*all->commands)->args. Input line to check and run if it
 * 									is executable.
 * 		2. function variables:
 * 			path_from_env. Path for the executable file.
 * 			i. Iterator for path.
 * 			path.
 * 			path. Flag. Can be 1 or 0.
 * 				path = path_to_executable(all). If 0 - the file is running.
 * 					if path not 0 and g_completion_code not zero, it was not
 * 					file and not command.
 * 			com_name. Command name or executable name.
 * Contains functions:
 * 		1.1. executable_check_and_run;
 * 		1.2. path_env;
 * 		1.3. join_directory_and_command;
 * 		1.4. completion_code_malloc_error;
*/

int	executable(t_all *all, t_command *tmp)
{
	char	**path_from_env;
	char    *com_name;
	int		i;
	int		path;

    g_completion_code = 0;
	path = executable_check_and_run(all, tmp->args[0], 1, tmp);
	if (path && g_completion_code == 127)
		return (1);
	if (!path || (path && g_completion_code))
		return (0);
	path_from_env = path_env(all);
	if (path_from_env == NULL)
		return (1);
	i = -1;
	path = -1;
	while (path_from_env[++i] && path == -1 && 0 == g_completion_code)
	{
        com_name = join_directory_and_command(path_from_env[i], tmp->args[0]);
        completion_code_malloc_error(com_name, tmp->args[0]);
        path = executable_check_and_run(all, com_name, 0, tmp);
    }
	return (path == -1);
}

/************************************
 * 	1.1. executable_check_and_run	*
 * **********************************
*/
/* Description:
 * 		The function checks if the path contains the entered string (checks
 * 		for the '/' character).
 * 		If the string consists entirely of a path, the message "is a
 * 		directory" is displayed.
 * 		If the path in the string is found and not the entire string is a
 * 		directory (are there characters after the last '/'), the function
 * 		tries to follow the specified path.
 * 		If the path does not exist or there is no file with the specified
 * 		name at the end of the path, the message "No such file or directory"
 * 		is displayed.
 * 		If the path is specified, it was possible to follow it, the function
 * 		tries to start the executable file.
 * Return value:
 * 		0 if executable was find and running.
 * 		-1 if file was find and not executable.
 * 		In other cases 1.
 * Contains functions:
 * 		1.1.1. check_command_sourse;
 * 		1.1.2. executable_error_print;
*/

int	executable_check_and_run(t_all *all, char *filename_with_path,
								int have_path, t_command *tmp)
{
    struct stat buf;

	if (check_command_sourse(filename_with_path))
		return (1);
    if (stat(filename_with_path, &buf) == 0 && buf.st_mode&S_IFDIR)
        return (executable_error_print(filename_with_path, ": is a directory\n", 126));
    else if (stat(filename_with_path, &buf) == 0 && buf.st_mode & S_IXUSR)
    {
        repointer_to_filename_with_path(&tmp->args[0], filename_with_path);
        if (tmp->end_flag&START_PIPE || tmp->end_flag&PIPE)
        {
            all->fd0 = pipe_23(all, tmp);
            return (0);
        }
        else
            return (fork_execve(all, filename_with_path));
    }
    else if (stat(filename_with_path, &buf) == 0)
        return (executable_error_print(filename_with_path, ": Permission denied\n", 126));
    else if (stat(filename_with_path, &buf) == -1)
    {
        if (have_path)
            return (executable_error_print(filename_with_path, ": No such file or directory\n", 126));
        else
            return (-1);
    }
	return (1);
}

/************************************
 * 	1.1.1. check_command_sourse		*
 * **********************************
*/
/* Description:
 * 		1) The function looks for the '/' character.
 * 		2) The function checks if only the '.'
 * 			Character has been entered.	If yes, completion code is set to 1.
 * Return value:
 * 		If the string com_name contain '/' character or	contain only '.',
 * 		return 1. Else it return 0.
*/

int	check_command_sourse(char *com_name)
{
    if (com_name[0] == '.' && com_name[1] == '\0')
    {
        write(STDERR_FILENO, "minishell: This command is missing from the", 43);
        write(STDERR_FILENO, " subject.\nIn the shell, . is a builtin com", 42);
        write(STDERR_FILENO, "mand in its own right, an alias for 'source", 43);
        write(STDERR_FILENO, "',which is used to read in a shell script a", 43);
        write(STDERR_FILENO, "nd execute its commands in the current shel", 43);
        write(STDERR_FILENO, "l rather than spawning a subshell, typicall", 43);
        write(STDERR_FILENO, "y used for scripts that set environment var", 43);
        write(STDERR_FILENO, "iables that you want to use later.\n", 35);
        return (g_completion_code = 1);
    }
    if (com_name[0] == '.' && com_name[1] == '.' && com_name[2] == '\0')
        return (g_completion_code = 127);
    if (!ft_strchr(com_name, '/'))
        return (1);
    return (0);
}

/************************************
 * 	1.1.2. executable_error_print	*
 * **********************************
*/
/* Description:
 * 		Set value error_code to *code_to_on. Print error message error_message
 * 		for input string com_name (command, directory, executable, etc.).
 * Return value:
 * 		Integer 1.
*/

int	executable_error_print(char *com_name, char *error_message, int error_code)
{
    write(STDERR_FILENO, "minishell: ", 12);
    write(STDERR_FILENO, com_name, ft_strlen(com_name));
    write(STDERR_FILENO, error_message, ft_strlen(error_message));
    g_completion_code = error_code;
    return (1);
}

/************************************
 * 				fork_execve			*
 * **********************************
*/
/* Description:
 * 		A function runs an executable using functions fork() and execve().
 * Return value:
 * 		Integer 0. If the file was found and the function launched it.
 * 		Else return not zero (1 or compiletion code).
*/

int		fork_execve(t_all *all, char *com_name)
{
    int		ret;
    pid_t	onepid;
    int		rv;

    ret = 2;
	onepid = fork();
    if (onepid == 0)
    {
        ret = execve(com_name, (*all->commands)->args, all->env);
        if (ret == -1)
        {
            exit(rv = 2);
        }
    }
    else if (onepid < 0)
    {
        write(STDERR_FILENO, "minishell: fork error. try again\n", 34);
        g_completion_code = 1;
        return (1);
    }
	wait_status_pipes(onepid);
    return (!ret);
}
