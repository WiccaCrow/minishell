#include "minishell.h"

/************************************
 * 		1.7. start_all				*
 * **********************************
*/
/* Description:
 * Start program with zero-structure (example, all 
 * pointers = NULL, int variables = 0, flag command = 0).
 *
 * Contain functions:
 *  1.7.1. init_env;
 *          do copy env
 *  1.7.2. init_commands;
 *          init our shell commands
 */

void	start_all(t_all *all, char **env, char *av0)
{
	ft_memset(all, 0, sizeof(t_all));
	g_completion_code = 0;
	all->pwd = getcwd(NULL, 0);
	init_env(all, env, av0);
	shlvl_set(all, 0, 0);
	all->history = get_history();
}
