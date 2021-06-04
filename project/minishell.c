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

	(void) ac;
	(void) av;
	start_all(&all, env);
//	line_getter(&all);
//	printf("\nline_getter result:\n\"%s\"\n", all.line);
//	if (all.line && dollar_handler(&all) && parser(&all))
//		executor(&all);
//	free(all.line);
//	all.line = NULL;
	
	while (1)
	{
		show_program_name();
//		if (fill_all(&all) != -1)
		if (line_getter(&all))
		{
			while (all.line && dollar_handler(&all) && parser(&all))
				executor(&all);
		}
		else
			break ;			
		free(all.args);
	}
	exit_clean(&all);
	return (0);
}

/************************************
 * 		1.1. start_all				*
 * **********************************
 * Start program with zero-structure (example, all 
 * pointers = NULL, int variables = 0, flag command = 0).
 *
 * function:
 *  1.1.1. init_env;
 *          do copy env
 *  1.1.2. init_commands;
 *          init our shell commands
 */

void	start_all(t_all *all, char **env)
{
	int	i;

	i = 0;
	all->flag_command = 0;
	all->return_code = 0;
	all->line = NULL;
	all->commands = NULL;
	init_env(all, env);
	all->history = get_history();
	while (all->env[i] && ft_strncmp(all->env[i], "PWD=", 4))
		++i;
	all->pwd = ft_strdup(&all->env[i][4]);
	init_commands(all);
}

/************************************
 * 		1.1.2. init_commands		*
 * **********************************
 * init our shell commands.
 *
 * function:
 *  libft. init_env;
 *          do copy env.
 */

void	init_commands(t_all *all)
{
	all->all_commands[0] = ft_strdup("echo");
	all->all_commands[1] = ft_strdup("cd");
	all->all_commands[2] = ft_strdup("pwd");
	all->all_commands[3] = ft_strdup("export");
	all->all_commands[4] = ft_strdup("unset");
	all->all_commands[5] = ft_strdup("env");
	all->all_commands[6] = ft_strdup("ctrl_c");
	all->all_commands[7] = ft_strdup("ctrl_d");
	all->all_commands[8] = ft_strdup("ctrl_slash");
	all->all_commands[9] = ft_strdup("exit");
}

/************************************
 * 		1.1.1. init_env     		*
 * **********************************
 *       do copy env;
 */

void	init_env(t_all *all, char **env)
{
    int i;

    i = -1;
    while (env[++i])
		;
    all->env = (char**)malloc(sizeof(char*) * (i + 1));
    all->env[i] = NULL;
	i = -1;
    while (env[++i])
        all->env[i] = ft_strdup(env[i]);
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
	write(STDOUT_FILENO, NONECOLOR, 4);
	return (0);
}

/************************************
 * 		1.5. exit_clean				*
 * **********************************
 * 	Clean exit.
*/

void	exit_clean(t_all *all)
{
	write_history(all->history);
	if (all->line)
	{
		free(all->line);
		all->line = NULL;
	}
	if (all->flag_command == exit_shell)
	{
		write(1, "exit\n",5);
		exit(0);
	}
	exit(1);
}
