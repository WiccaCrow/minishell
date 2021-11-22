#include "minishell.h"

/************************************
 * 	1.3.5.7. exec_unset				*
 * **********************************
*/
/* Description:
 * 		Each variable or function 
 * 		specified by name shall be 
 * 		unset.
 * 
 * Contains functions:
 * 	1.3.5.6.1.	count_env_lines;
 * 	1.3.5.6.3.1.1.	count_lines;
 * 	1.3.5.7.1.	exec_unset_find_env_str;
 * 	1.3.5.7.2.	exec_unset_do_new_env;
 */

int	exec_unset(t_all *all, t_command *tmp)
{
	char	**env_new;
	int		i_old;
	int		i_new;

	g_completion_code = 0;
	i_old = count_env_lines(all);
	i_new = count_lines(all, tmp, "unset", i_old);
	if (i_new < 0)
		i_new = 0;
	if (i_new == i_old)
		return (0);
	env_new = (char **)malloc((i_new + 1) * sizeof(char *));
	env_new[i_new] = NULL;
	if (env_new)
	{
		if (i_old)
			exec_unset_find_env_str(all, tmp, "unset");
		exec_unset_do_new_env(all, env_new, i_new, i_old);
	}
	else
		completion_code_malloc_error(NULL, "unset");
	return (0);
}

/****************************************
 * 	1.3.5.7.1. exec_unset_find_env_str	*
 * **************************************
*/
/* Description:
 * 		This function checks arguments 
 * 		for validity. In the env array, 
 * 		finds strings with these valid 
 * 		arguments. If the strings are 
 * 		found, the function free this 
 * 		memory and set its pointer to 
 * 		NULL.
 * 
 * 		oper_name - "export" or "unset".
 * 
 * Contains functions
 * 		1.3.5.6.3.1.1.1. check_valid_args;
 * 		1.3.5.6.3.1.1.3. find_env_str;
 * 		1.4. ft_free;
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
			ft_free((void **)all->env + index_env_str);
	}
}

/********************************************
 * 	1.3.5.7.2.  exec_unset_delete_env_str	*
 * ******************************************
*/
/* Description:
 * 		The function fills a new array with non-zero 
 * 		strings from the old array, and then frees 
 * 		memory from under the old two-dimensional 
 * 		array and changes the pointer from the freed 
 * 		memory to the new array.
 */

void	exec_unset_do_new_env(t_all *all, char **env_new,
			int nb_lines, int nb_old_env)
{
	int	index_new;
	int	index_old;

	index_new = -1;
	index_old = 0;
	while (++index_new < nb_lines)
	{
		while (all->env[index_old] == NULL && index_old < nb_old_env)
			++index_old;
		env_new[index_new] = all->env[index_old++];
	}
	free(all->env);
	all->env = env_new;
}
