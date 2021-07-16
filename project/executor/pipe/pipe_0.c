#include "minishell.h"

/************************************
 * 				enter_the_pipes		*
 * **********************************
*/
/* Description:
 * 		The function runs commands with pipes for parallel 
 *		execution as follows:
 *		1. using the nb_pipes function, an array is created to 
 * 			fill with the child process identifiers (the array 
 * 			is filled in the next function).
 * 		2. in the do_pipes function, commands are launched in 
 * 			child processes and the array created by the 
 * 			nb_pipes function is filled.
 * 		3. In the wait_status_fork function, the parent process 
 * 			waits for all child processes to terminate and the 
 * 			termination code is filled into the 
 * 			g_completion_code variable.
 * Code comments:
 * 		pid_t *pid. Array of pids (pid[i] = fork()).
 * 		all->fd0 = tmp->input_fd; Can be not 0, if was redirect.
 * Contains functions:
 * 	nb_pipes;
 * 	do_pipes;
 * 	wait_status_fork;
*/

void	enter_the_pipes(t_all *all, t_command *tmp)
{
	int		nb_p;
	pid_t	*pid;

	if (NULL == nb_pipes(tmp, &pid))
		return ;
	all->fd0 = tmp->input_fd;
	nb_p = do_pipes(all, tmp, pid);
	all->waitpid = -1;
	while (nb_p--)
		if (pid[++(all->waitpid)] > 0)
			wait_status_fork(pid[all->waitpid]);
	signal(SIGINT, sigint_handler);
	free(pid);
}

/************************************
 * 				nb_pipes			*
 * **********************************
*/
/* Description:
 * 		The function allocates a memory area for 
 * 		pid_t *pid array for process or process 
 * 		group IDs (return value from function fork()).
 * 
 * Return value::
 * 		Pointer to allocates a memory area for 
 * 		pid_t *pid.
 * Contains functions:
 * 	completion_code_malloc_error;
*/

pid_t	*nb_pipes(t_command *tmp, pid_t **pid)
{
	t_command	*for_count;
	int			nb_p;

	nb_p = 0;
	for_count = tmp;
	while (for_count->end_flag & PIPE)
	{
		++nb_p;
		for_count = for_count->next;
		if (for_count == NULL)
			break ;
	}
	*pid = (pid_t *)malloc((nb_p + 1) * sizeof(pid_t));
	if (NULL == *pid)
		completion_code_malloc_error(NULL, "pipes");
	return (*pid);
}

/************************************
 * 				do_pipes			*
 * **********************************
*/
/* Description:
 * 		In the do_pipes function, commands are launched in 
 * 		child processes and the array created by the 
 * 		nb_pipes function is filled.
 * Code comments:
 * 		pid_t *pid. Array of pids (pid[i] = fork()).
 * 		-------------------
 * 		(tmp->end_flag&PIPE || tmp->end_flag&START_PIPE). 
 * 			Command start or end with pipe.
 * 		-------------------
 * 		if (tmp->flag_command == 0)...  Here fill path for 
 * 			executable or g_copletion_code.
 * 		-------------------
 * 		if (tmp->end_flag&PIPE)... running commands ending 
 * 			in pipe.
 * 		-------------------
 * 		else if (-1 == pipe_last(all, tmp)). Running 
 * 			commands only start in pipe, but not ending in 
 * 			pipe.
 * 		-------------------
 * Return value:
 * 		int. Number of commanders separated by pipes.
 * Contains functions:
 * 	command_not_found; for filling path to executable.
 * 	pipe_1st_midle; running commands ending in pipe.
 * 	pipe_last; running commands only start in pipe, 
 * 		but not ending in pipe.
*/

int	do_pipes(t_all *all, t_command *tmp, pid_t *pid)
{
	int	nb_p;

	nb_p = 0;
	while (tmp->end_flag & PIPE || tmp->end_flag & START_PIPE)
	{
		g_completion_code = 0;
		if (tmp->flag_command == 0)
			command_not_found(all, tmp);
		if (tmp->end_flag & PIPE)
		{
			all->fd0 = pipe_1st_midle(all, tmp);
			if (pipe_fork_if_error(all))
				break ;
		}
		else if (-1 == pipe_last(all, tmp))
			break ;
		pid[nb_p++] = all->waitpid;
		tmp = tmp->next;
		if (tmp == NULL)
			break ;
	}
	return (nb_p);
}

/************************************
 * 			pipe_fork_if_error		*
 * **********************************
*/
/* Description:
 * 		If all->fd < 0 print error message to STDERR_FILENO.
 * 
 * Return value::
 * 		0 if all->fd >=0.
 * 		1 if all->fd < 0.
 * Contains functions:
 * 	completion_code_int_ret_error;
 * 	completion_code_fork_error;
*/

int	pipe_fork_if_error(t_all *all)
{
	if (all->fd0 >= 0)
		return (0);
	if (-1 == all->fd0)
		completion_code_int_ret_error("minishell: pipes (pipe -1): ", 1);
	else if (-2 == all->fd0)
		completion_code_fork_error("minishell: pipes (fork -1): ",
			"fork error\n", 1);
	return (1);
}

/************************************
 * 		exec_command_with_pipe		*
 * **********************************
*/
/* Description:
 * 		Execute tmp->args[0] command (for pipes).
 *
 * Return value::
 * 		0 if all->fd >=0.
 * 		1 if all->fd < 0.
 * Contains functions:
 * 	executor;
 * 	exit_clean;
*/

void	exec_command_with_pipe(t_all *all, t_command *tmp)
{
	if (tmp->input_fd >= 0)
	{
		if (tmp->flag_command == 0 && g_completion_code == 0)
		{
			if (-1 == execve(tmp->args[0], tmp->args, all->env))
			{
				write(STDERR_FILENO, "minishell: pipes: fork: error: \n", 32);
				write(STDERR_FILENO, "execve return -1. Try again.\n", 29);
			}
		}
		else if (0 == g_completion_code)
			executor(all, tmp);
	}
	else
	{
		g_completion_code = 1;
		exit_clean(all);
	}
}
