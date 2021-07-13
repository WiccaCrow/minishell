#include "minishell.h"

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

void	start_all(t_all *all, char **env, char *av0)
{
	ft_memset(all, 0, sizeof(t_all));
	g_completion_code = 0;
	all->parse_error = 0;
	all->line = NULL;
	all->commands = NULL;
	all->pwd = getcwd(NULL, 0);
	all->env = NULL;
	init_env(all, env, av0);
	shlvl_set(all, 0, 0);
	all->history = get_history();
}