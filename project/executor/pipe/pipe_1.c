#include "minishell.h"

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
 * 	pipe_last_dup;
 * 	exec_command_with_pipe;
 * 	exit_clean;
 * 	completion_code_fork_error;
*/

int	pipe_last(t_all *all, t_command *tmp)
{
	signal(SIGINT, SIG_IGN);
	all->waitpid = fork();
	if (!all->waitpid)
	{
		signal(SIGINT, sigint_handler);
		pipe_last_dup(all, tmp);
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
 * 			pipe_last_dup			*
 * **********************************
*/
/* Description:
 * 		The function do dup2() for function pipe_last().
 *
 * Contains functions:
 * 	completion_code_int_ret_error;
 * 	exit_clean;
*/

void	pipe_last_dup(t_all *all, t_command *tmp)
{
	int	err_dup;

	err_dup = 0;
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
}

/************************************
 * 			pipe_1st_midle			*
 * **********************************
*/
/* Description:
 * 		The function running commands ending in pipe.
 * 
 * Contains functions:
 * 	pipe_1st_midle_dup;
 * 	exec_command_with_pipe;
 * 	exit_clean;
*/

int	pipe_1st_midle(t_all *all, t_command *tmp)
{
	int	file_pipes[2];

	if (pipe(file_pipes) == 0)
	{
		signal(SIGINT, SIG_IGN);
		all->waitpid = fork();
		if (!all->waitpid)
		{
			signal(SIGINT, sigint_handler);
			pipe_1st_midle_dup(all, tmp, file_pipes);
			exec_command_with_pipe(all, tmp);
			exit_clean(all);
		}
		return (pipe_1st_midle_return_closefd(all, tmp, file_pipes));
	}
	if (tmp->end_flag & START_PIPE)
		close(all->fd0);
	return (-1);
}

/****************************************
 * 		pipe_1st_midle_return_closefd	*
 * **************************************
*/
/* Description:
 * 		The function close old fd (all->fd0) and return new output fd or -2 in
 * 		case fork error (all->waitpid == -1).
 * Return value:
 * 		new output fd or -2 if was fork error.
*/

int	pipe_1st_midle_return_closefd(t_all *all, t_command *tmp, int *file_pipes)
{
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

/************************************
 * 			pipe_1st_midle_dup		*
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

void	pipe_1st_midle_dup(t_all *all, t_command *tmp, int *file_pipes)
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
