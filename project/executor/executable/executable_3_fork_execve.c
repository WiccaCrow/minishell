#include "minishell.h"

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

void	fork_execve(t_all *all, t_command *tmp)
{
	pid_t	onepid;

	signal(SIGINT, SIG_IGN);
	onepid = fork();
	if (onepid == 0)
	{
		fork_execve_if_fork(all, tmp);
	}
	else if (onepid < 0)
	{
		write(STDERR_FILENO, "minishell: fork error. try again\n", 34);
		g_completion_code = 1;
	}
	wait_status_fork(onepid);
	signal(SIGINT, sigint_handler);
}

/************************************
 * 			fork_execve_if_fork		*
 * **********************************
*/
/* Description:
 * 		A function runs an executable execve() inside fork().
 * Return value:
 * 		Integer 0. If the file was found and the function launched it.
 * 		Else return 2.
*/

void	fork_execve_if_fork(t_all *all, t_command *tmp)
{
	int	ret;

	ret = 2;
	signal(SIGINT, sigint_handler);
	if (tmp->input_fd != -1)
		dup2(tmp->input_fd, 0);
	dup2(tmp->output_fd, 1);
	if (tmp->input_fd != -1)
	{
		ret = execve(tmp->args[0], tmp->args, all->env);
		if (ret == -1)
			exit (1);
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
		g_completion_code = 128 + WTERMSIG(status);
	else
		st = WIFSTOPPED(status);
	if (!ex && !ter && st)
		g_completion_code = WSTOPSIG(status);
}
