#include "minishell.h"

//int	pipe_23(t_all *all, t_command *tmp)//запускает на исполнение команды с пайпами между команд в функции pipe_1st_midle, команду после последнего пайпа в функции pipe_last
//{
//	if (tmp->end_flag&PIPE)
//		return (pipe_1st_midle(all, tmp));
//	else
//		return (pipe_last(all, tmp));
//}

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
		if (tmp->flag_command == 0 && g_completion_code == 0)
			execve(tmp->args[0], tmp->args, all->env);          // cat теперь должен получить мою строку "123" и вывести в терминал
		else if (g_completion_code == 0)
			executor(all, tmp);
		exit (g_completion_code);
	}
	close(all->fd0);
	wait_status_fork(all->waitpid);
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

			if (tmp->flag_command == 0 && g_completion_code == 0)
				execve(tmp->args[0], tmp->args, all->env);            // ls теперь записан в 1
			else if (g_completion_code == 0)
				executor(all, tmp);
			exit (g_completion_code);
		}
		if (tmp->end_flag&START_PIPE && tmp->end_flag&PIPE)
			close(all->fd0);
		close(file_pipes[1]);
		wait_status_fork(all->waitpid);
		return (file_pipes[0]);
	}
	return (0);
}

int	all_pipes(t_all *all, t_command *tmp)// запускает на параллельное выполнение команды с пайпами
{
	all->fd0 = tmp->input_fd;

	while (tmp->end_flag&PIPE || tmp->end_flag&START_PIPE)
	{
		g_completion_code = 0;
		if (tmp->flag_command == 0)
			executor(all, tmp);
		if (tmp->end_flag&PIPE)
			all->fd0 = pipe_1st_midle(all, tmp);
		else
			pipe_last(all, tmp);
		tmp = tmp->next;
		if (tmp == NULL)
			break;
		g_completion_code = 0;
	}
	return (0);
}

//int	nb_pipes(t_command *tmp)//считатет количество пайпов подряд
//{
//	t_command *for_count;
//	int	nb_p;
//
//	all->waitpid = 0;///////////////////////
//	nb_p = 0;
//	for_count = tmp;
//	while (for_count->end_flag&PIPE)
//	{
//		++nb_p;
//		for_count = for_count->next;
//		if (for_count == NULL)
//			break;
//	}
//	return (nb_p);
//}
