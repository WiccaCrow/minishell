#include "minishell.h"

int pipe_last(t_all *all, t_command *tmp)//исполняет команду, которая только начинается на пайп (команда после последнего пайпа)
{
	all->waitpid = fork();
	if (!all->waitpid)                                        // executor();
	{
		if (tmp->output_fd != 1)
			dup2(tmp->output_fd, 1);
		if (tmp->input_fd == 0)
			dup2(all->fd0, tmp->input_fd);
		else
			dup2(tmp->input_fd, 0);                       // всё, что читалось бы из терминала, теперь читается из того места, куда записалось file_pipes[1] (то есть 1 после dup2)
		if (tmp->input_fd >= 0)
		{
			if (tmp->flag_command == 0 && g_completion_code == 0)
				execve(tmp->args[0], tmp->args,
					   all->env);          // cat теперь должен получить мою строку "123" и вывести в терминал
			else if (g_completion_code == 0)
				executor(all, tmp);
		}
		else
		{
			g_completion_code = 1;
			exit_clean(all);
			// exit(1);
		}
		exit_clean(all);
	}
	close(all->fd0);
	return (0);
}

int	pipe_1st_midle(t_all *all, t_command *tmp)//исполняет все команды, которые заканчиваются на пайп
{
	int	file_pipes[2];

	if (pipe(file_pipes) == 0)
	{
		all->waitpid = fork();
		if (!all->waitpid)
		{
			if (tmp->output_fd == 1)
				dup2(file_pipes[1], tmp->output_fd);                         // всё, что писалось бы в терминал, теперь пишется в то место, куда записалось file_pipes[1] (то есть после dup2)
			else
				dup2(tmp->output_fd, 1);

			dup2(file_pipes[1], tmp->output_fd);                         // всё, что писалось бы в терминал, теперь пишется в то место, куда записалось file_pipes[1] (то есть после dup2)

			close(file_pipes[0]);

			if (tmp->input_fd == 0)
				dup2(all->fd0, tmp->input_fd);
			else
				dup2(tmp->input_fd, 0);
			if (tmp->input_fd >= 0)
			{
				if (tmp->flag_command == 0 && g_completion_code == 0)
					execve(tmp->args[0], tmp->args, all->env);            // ls теперь записан в 1
				else if (g_completion_code == 0)
					executor(all, tmp);
			}
			else
			{
				g_completion_code = 1;
				exit_clean(all);
				// exit(1);
			}
			exit_clean(all);
		}
		if (tmp->end_flag&START_PIPE && tmp->end_flag&PIPE)
			close(all->fd0);
		close(file_pipes[1]);
		return (file_pipes[0]);
	}
	return (0);
}

/************************************
 * 				all_pipes			*
 * **********************************
*/
/* Description:
 * 		The function launches a command with 
 * 		pipes for parallel execution.
 * Code comments:
 * 		pid_t *pid. Array of pids (pid[i] = fork()).
 * 		all->fd0 = tmp->input_fd; Can be not 0, if was redirect.
 * 		(tmp->end_flag&PIPE || tmp->end_flag&START_PIPE). 
 * 			Command start or end with pipe.
*/

void	all_pipes(t_all *all, t_command *tmp)
{
	int		nb_p;
	pid_t	*pid;

	nb_p = 0;
	pid = nb_pipes(tmp);
	if (NULL == pid)
	{
		completion_code_malloc_error(NULL, "pipes");
		return ;
	}
	all->fd0 = tmp->input_fd;
	while (tmp->end_flag&PIPE || tmp->end_flag&START_PIPE)
	{
		g_completion_code = 0;
		if (tmp->flag_command == 0)
			command_not_found(all, tmp);
		if (tmp->end_flag&PIPE)
			all->fd0 = pipe_1st_midle(all, tmp);
		else
			pipe_last(all, tmp);
		pid[nb_p++] = all->waitpid;
		tmp = tmp->next;
		if (tmp == NULL)
			break;
		// g_completion_code = 0;
	}
	all->waitpid = 0;
	while (nb_p--)
		wait_status_fork(pid[all->waitpid++]);
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
*/

pid_t	*nb_pipes(t_command *tmp)
{
	t_command	*for_count;
	int			nb_p;
	pid_t		*pid;

	nb_p = 0;
	for_count = tmp;
	while (for_count->end_flag&PIPE)
	{
		++nb_p;
		for_count = for_count->next;
		if (for_count == NULL)
			break;
	}
	pid = (pid_t*)malloc(nb_p * sizeof(pid_t));
	return (pid);
}
