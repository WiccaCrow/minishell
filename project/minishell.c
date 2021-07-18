#include "minishell.h"
int	g_completion_code; // код возврата ошибки $?

/************************************
 * 		1. main						*
 * **********************************
*/
/* Description:
 * The start of the program begins in the minishell.c 
 * file with the main () function.
 */

/*
 * functions:
 * 1.1. start_all;
 * 			Start program with zero-structure (example, 
 * 			all pointers = NULL, int variables = 0).
 * 1.2. show_program_name;
 * 			Prints the name of the program to standard 
 * 			output (terminal). In our program, this 
 * 			will happen every time the shell is waiting 
 * 			for a command from the user.
 * 1.3. fill_all;
 * 			This function performs several important 
 * 			operations:
 * 			1) checks the validity of the data entered 
 * 				by the user into the shell command line, 
 * 				sets the data validity flag in the t_all 
 * 				structure.
 * 				flag:		1 - data is not valid.
 * 			2) based on these data, fills in the main 
 * 				structure of the program. t_all all.
 * 1.4. executor;
 * 			Look README for more information (operation 
 * 			flags).
 * 				Accepts a data-ready structure.
 * 			Checks the flags of the operations in the 
 * 			structure.
 * 				Applies functions corresponding to flags 
 * 			to data.
 * 				Prints the result or error to standard 
 * 			output as needed.
 * 1.5. exit_clean;
 * 			Clean exit.
*/

/**
 * Мэйн на ридлайне для дебага
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
 * 			 ft_free				*
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
 * 		1.2. show_program_name		*
 * **********************************
*/
/* Description:
 * 	Prints the name of the program to standard 
 * output (terminal). In our program, this will 
 * happen every time the shell is waiting for a 
 * command from the user.
*/

int	show_program_name(void)
{
	write(STDOUT_FILENO, GOLD, 8);
	write(STDOUT_FILENO, NAME, ft_strlen(NAME));
	write(STDOUT_FILENO, NONECOLOR, 4);
	return (0);
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
