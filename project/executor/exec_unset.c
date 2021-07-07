#include "minishell.h"

/************************************
 * 			 exec_unset				*
 * **********************************
*/
/* Description:
 * 		Each variable or function 
 * 		specified by name shall be 
 * 		unset.
 * 
 * Contains functions:
 * 		count_env_lines;
 * 		count_lines;
 * 		exec_unset_find_env_str;
 * 		exec_unset_do_new_env;
 */

int	exec_unset(t_all *all, t_command *tmp)
{
	char	**env_new;
	int		i;

	g_completion_code = 0;
	i = count_env_lines(all);
	i = count_lines(all, tmp, "unset", i);
	env_new = (char **)malloc((i + 1) * sizeof(char *));
	env_new[i] = NULL;
	if (!env_new)
		completion_code_malloc_error(NULL, "unset");
	if (g_completion_code == 0)
	{
		exec_unset_find_env_str(all, tmp, "unset");
		exec_unset_do_new_env(all, env_new, i);
	}
	return (0);
}

/************************************
 * 		 exec_unset_find_env_str	*
 * **********************************
*/
/* Description:
 * 		This function checks arguments 
 * 		for validity. In the env array, 
 * 		finds strings with these valid 
 * 		arguments. If the strings are 
 * 		found, the function sets first 
 * 		charfrees in string to '\0'.
 * 
 * 		oper_name - "export" or "unset".
 * 
 * Contains functions
 * 		check_valid_args;
 * 		find_env_str;
 */

void	exec_unset_find_env_str(t_all *all, t_command *tmp, char *oper_name)
{
	int	index_env_str;

	all->nb_arg = -1;
	while (tmp->args[++all->nb_arg])
	{
		if (!check_valid_args(tmp->args[all->nb_arg], oper_name, 0))
			continue ;
		index_env_str = find_env_str(all, tmp, oper_name, all->env);
		if (all->env[index_env_str] != NULL)
			all->env[index_env_str][0] = 0;
	}
}

/************************************
 * 	  exec_unset_delete_env_str		*
 * **********************************
*/
/* Description:
 * 		The function replaces the old 
 * 		env array with the new env 
 * 		array.
 *  	The function frees the memory 
 *      allocated for strings with '\0'
 *      first char and redirects pointers 
 * 		from this strings to NULL.
 */

void	exec_unset_do_new_env(t_all *all, char **env_new, int nb_lines)
{
	int	j;
	int	i;

	j = -1;
	i = 0;
	while (++j < nb_lines)
	{
		while (all->env[j + i] != NULL && all->env[j + i][0] == 0)
		{
			free(all->env[j + i]);
			all->env[j + i] = NULL;
			++i;
		}
		env_new[j] = all->env[j + i];
	}
	free(all->env);
	all->env = env_new;
}
