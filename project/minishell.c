#include "minishell.h"
int	g_completion_code;

/************************************
 *		1. main						*
 * **********************************
*/
/* Description:
 * The start of the program begins in the minishell.c 
 * file with the main () function.
 */
/*
 * Contains functions:
 * 1.1. sigint_handler; (in sigint_handler.c)
 * 1.2. sigquit_handler; (in signal_handler.c)
 * 1.3. main_cycle;
 * 1.4. ft_free;
 * 1.5. exit_clean;	Clean exit.
 * 1.6. line_getter; (in line_getter.c)
*/

int	main(int ac, char **av, char **env)
{
	t_all	all;

	(void) ac;
	(void) av;
	g_completion_code = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	start_all(&all, env, av[0]);
	while (1)
	{
		if (line_getter(&all))
			main_cycle(&all);
		else
			break ;
		ft_free((void **)&all.line);
	}
	exit_clean(&all);
	return (0);
}

/************************************
 * 		1.3. main_cycle				*
 * **********************************
*/
/* Description:
 * The function does commands and executables in cycle.
 */
/*
 * Contains functions:
 * 1.3.1. check_line;
 * 1.3.2. 2dollar_handler;
 * 1.3.3. parser2;
 * 1.3.4. enter_the_pipes;
 * 1.3.5. executor;
 * 1.3.6. free_commands;
*/
int	main_cycle(t_all *all)
{
	while (all->line && *(all->line) && check_line(all) && \
			dollar_handler(all) && parser2(all))
	{
		if ((*(all->commands))->end_flag & START_PIPE || \
					(*(all->commands))->end_flag & PIPE)
			enter_the_pipes(all, *(all->commands));
		else if ((*(all->commands))->input_fd != -1)
			executor(all, *(all->commands));
	}
	if (all->check_line)
		free_commands(&(all->commands));
	return (0);
}

/************************************
 * 			 1.4. ft_free			*
 * **********************************
*/
/* Description:
 * 	Your pointer is *pointer. Example:
 *		char *str;
 *		ft_free((void**)&str);
 * 	The function free pointer if pointer not NULL.
*/

void	ft_free(void **pointer)
{
	if (*pointer)
	{
		free(*pointer);
		*pointer = NULL;
	}
}

/************************************
 * 		1.5. exit_clean				*
 * **********************************
*/
/* Description:
 * 	Clean exit.
*/

void	exit_clean(t_all *all)
{
	int	i;

	wr_history(all->history);
	if (all->line)
	{
		free(all->line);
		all->line = NULL;
	}
	if (all->env)
	{
		i = -1;
		while (all->env[++i])
			ft_free((void **)&all->env[i]);
		free(all->env);
		all->env = NULL;
	}
	ft_free((void **)&all->pwd);
	free_commands(&all->commands);
	exit(g_completion_code);
}
