#include "minishell.h"

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

/************************************
 * 				pipe_last			*
 * **********************************
*/
/* Description:
 * 		Running commands only start in pipe, 
 * 		but not ending in pipe.
 * 
 * Return value::
 * 		0 if all good.
 * 		-1 if fork() returned -1.
 * Contains functions:
 * 	exec_command_with_pipe;
 * 	exit_clean;
 * 	completion_code_fork_error;
*/

int	pipe_last(t_all *all, t_command *tmp)
{
	int	err_dup;

	err_dup = 0;
	all->waitpid = fork();
	if (!all->waitpid)
	{
		if (1 != tmp->output_fd)
			err_dup = dup2(tmp->output_fd, 1);
		if (0 == tmp->input_fd && err_dup != -1)
			err_dup = dup2(all->fd0, tmp->input_fd);
		else if (-1 != err_dup)
			err_dup = dup2(tmp->input_fd, 0);
		if (-1 == err_dup)
		{
			completion_code_int_ret_error("minishell: pipe_last: dup err: ", 1);
			exit_clean(all);
		}
		exec_command_with_pipe(all, tmp);
		exit_clean(all);
	}
	close(all->fd0);
	if (-1 == all->waitpid)
		return (completion_code_fork_error("minishell: pipes (fork -1): ",
				"fork error\n", 1));
	return (0);
}

/************************************
 * 			pipe_1st_midle			*
 * **********************************
*/
/* Description:
 * 		Function running commands ending in pipe.
 * 
 * Contains functions:
 * 	dupfd_in_pipe_1st_midle;
 * 	exec_command_with_pipe;
 * 	exit_clean;
*/

int	pipe_1st_midle(t_all *all, t_command *tmp)
{
	int	file_pipes[2];

	if (pipe(file_pipes) == 0)
	{
		all->waitpid = fork();
		if (!all->waitpid)
		{
			dupfd_in_pipe_1st_midle(all, tmp, file_pipes);
			exec_command_with_pipe(all, tmp);
			exit_clean(all);
		}
		if (tmp->end_flag & START_PIPE && tmp->end_flag & PIPE)
			close(all->fd0);
		close(file_pipes[1]);
		if (-1 == all->waitpid)
		{
			close (file_pipes[0]);
			return (-2);
		}
		return (file_pipes[0]);
	}
	if (tmp->end_flag & START_PIPE)
		close(all->fd0);
	return (-1);
}

/************************************
 * 		dupfd_in_pipe_1st_midle		*
 * **********************************
*/
/* Description:
 * 		Function configures file descriptors for input 
 * 		and output for pipe-separated commands.
 * 
 * Contains functions:
 * 	completion_code_int_ret_error;
 * 	exit_clean;
*/

void	dupfd_in_pipe_1st_midle(t_all *all, t_command *tmp, int *file_pipes)
{
	int	err_dup;

	if (tmp->output_fd == 1)
		err_dup = dup2(file_pipes[1], tmp->output_fd);
	else
		err_dup = dup2(tmp->output_fd, 1);
	if (-1 != err_dup)
		err_dup = dup2(file_pipes[1], tmp->output_fd);
	close(file_pipes[0]);
	if (-1 != err_dup)
	{
		if (tmp->input_fd == 0)
			err_dup = dup2(all->fd0, tmp->input_fd);
		else
			err_dup = dup2(tmp->input_fd, 0);
	}
	if (-1 == err_dup)
	{
		completion_code_int_ret_error("minishell: dupfd_in_pipe_1st_midle: ",
			1);
		exit_clean(all);
	}
}
