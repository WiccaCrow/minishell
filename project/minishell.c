#include "./includes/minishell.h"

/************************************
 * 		1. main						*
 * **********************************
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

int main(int ac, char **av, char **env)
{
	t_all	all;

	start_all(&all);
	while (!all.flag_exit)
	{
		show_program_name();
		fill_all(&all);
		executor(&all);
	}
	exit_clean(&all, 0);
	return (0);
}

/************************************
 * 		1.1. start_all				*
 * **********************************
 * Start program with zero-structure (example, all 
 * pointers = NULL, int variables = 0).
 */

void	start_all(t_all *all)
{
	init_env(all);
	all->flag_executer = 0;
	all->flag_exit = 0;
	all->line = NULL;	
}

/************************************
 * 		1.2. show_program_name		*
 * **********************************
 * 	Prints the name of the program to standard 
 * output (terminal). In our program, this will 
 * happen every time the shell is waiting for a 
 * command from the user.
*/

int show_program_name(void)
{
	write(STDOUT_FILENO, GOLD, 8);
	write(STDOUT_FILENO, NAME, ft_strlen(NAME));
	write(STDOUT_FILENO, NONECOLOR, 5);
	return (0);
}

/************************************
 * 		1.3. fill_all				*
 * **********************************
 * This function performs several important operations:
 * 	1) checks the validity of the data entered 
 * 		by the user into the shell command line, 
 * 		sets the data validity flag in the t_all 
 * 		structure.
 * 				flag:		1 - data is not valid.
 * 	2) based on these data, fills in the main 
 * 		structure of the program. t_all all.
*/

void	fill_all(t_all *all)
{
	int	ret;

	ret = 1;
	while (ret != -1)
	{
		ret = get_next_line(1, &all->line);
		command = parser(all->line);
		executor(command);
		printf("Hi from main, command:\n\"%s\"\n", command);
		show_program_name();
		ret = get_next_line(1, &line);
	}
}

/************************************
 * 		1.4. executor				*
 * **********************************
 * Look README for more information (operation flags).
 * Accepts a data-ready structure.
 * Checks the flags of the operations in the structure.
 * Applies functions corresponding to flags to data.
 * Prints the result or error to standard output as 
 * needed.
 * 1.5. exit_clean;
 * 			Clean exit.
*/

/************************************
 * 		1.5. exit_clean				*
 * **********************************
 * 	Clean exit.
*/

void	exit_clean(t_all *all, int exit_code)
{
	if (all->line)
	{
		free(all->line);
		all->line = NULL;
	}
	if (all->flag_executer == 1)
		exit(0);
	else if (exit_code)
		exit(exit_code);
}
