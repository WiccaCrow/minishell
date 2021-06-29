#include "minishell.h"

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

int main(int ac, char **av, char **env)
{
	t_all	all;

	(void) ac;
	(void) av;
//	signal(SIGINT, sigint_handler);

	start_all(&all, env);

	while (1)
	{
		if (fill_all(&all) != -1)
		{
			while (all.line && *all.line && check_line(&all) && \
			dollar_handler(&all) && parser2(&all))
			{
                if ((*all.commands)->end_flag & START_PIPE || (*all.commands)->end_flag & PIPE)
                    all_pipes(all.commands, all.env);
                else
                    executor(&all);
            }
		}
		else
			break ;
		free(all.line);
		all.line = NULL;
	}
	exit_clean(&all);
	return (0);
}

/************************************
 * 		1.1. start_all				*
 * **********************************
*/
/* Description:
 * Start program with zero-structure (example, all 
 * pointers = NULL, int variables = 0, flag command = 0).
 *
 * Contain functions:
 *  1.1.1. init_env;
 *          do copy env
 *  1.1.2. init_commands;
 *          init our shell commands
 */

void	start_all(t_all *all, char **env)
{
	int	i;

	i = 0;
	all->completion_code = 0;/////////////////////
    g_completion_code = 0;
	all->parse_error = 0;
	all->line = NULL;
	all->commands = NULL;
	all->pwd = getcwd(NULL, 0);
	init_env(all, env);
	shlvl_set(all);
	all->history = get_history();
	while (all->env[i] && ft_strncmp(all->env[i], "PWD=", 4))
		++i;
}

/************************************
 * 		1.1.1. init_env     		*
 * **********************************
*/
/* Description:
 *       do copy env;
 * 		Function add OLDPWD and add PWD with 
 * 		real pwd value if env don't contain 
 * 		PWD or OLDPWD.
 */

void	init_env(t_all *all, char **env)
{
    int i;
	int	index_oldpwd;
	int	index_pwd;

    i = -1;
    while (env[++i])
		;
	index_oldpwd = get_my_env_index(env, "OLDPWD", 6);
	index_pwd = get_my_env_index(env, "PWD", 3);
	if (!env[index_oldpwd] && !env[index_pwd])
		i +=2;
	else if (!env[index_oldpwd] || !env[index_pwd])
		i += 1;
    all->env = (char**)malloc(sizeof(char*) * (i + 1));
    all->env[i] = NULL;
	i = -1;
    while (env[++i])
        all->env[i] = ft_strdup(env[i]);
	if (env[index_oldpwd] == NULL)
		all->env[i] = ft_strdup("OLDPWD");
	if (env[index_pwd] == NULL)
		all->env[++i] = ft_strjoin("PWD=", all->pwd);
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
*/
/* Description:
 * 	Clean exit.
*/

void	exit_clean(t_all *all)
{
	wr_history(all->history);
	if (all->line)
	{
		free(all->line);
		all->line = NULL;
	}
	close_fd_output_input(all);
	all_args_free(all);
	exit(g_completion_code);
}
