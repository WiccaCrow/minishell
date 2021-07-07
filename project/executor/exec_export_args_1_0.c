#include "minishell.h"

/************************************
 * 				subjoin_env			*
 * **********************************
*/
/* Start variables value:
 * 		subjoin_env(all, i, -1);
 * Variables description, code comments:
 * 		char **env_new; future new env-array with new env variables.
 * 		int index; the index of the search string in the current env array.
 * 		if (all->env[index] == NULL)
 * 			env_new[--i] = ft_strdup(tmp->args[j]);
 * 			if in the env array was no such variable, create it.
 * Description:
 * 		The export command allow parameters and functions to be added to and
 * 		deleted from the environment. If the value of a parameter in the
 * 		environment is modified, the new value becomes part of the
 * 		environment, replacing the old.
 * 		The environment inherited by any executed command consists of the
 * 		shell’s initial environment, whose values may be modified in the
 * 		shell, less any pairs removed by the unset command, plus any additions
 * 		via the export command.
 * Code comments:
 * 		If malloc error occurs all->env not change;
 * Contains functions:
 * 		1. count_lines;
 * 		2. export_args_to_new_env;
 * 			Add new variable to my env array or	overwrites existing env
 * 			variable with new value.
*/

void	subjoin_env(t_all *all, t_command *tmp, int i)
{
	char	**env_new;
	int		err_malloc;

	env_new = create_new_env_array(all, tmp, i);
	if (!env_new)
		return ;
	err_malloc = export_args_to_new_env(all, tmp, env_new);
	if (!err_malloc)
	{
		free(all->env);
		all->env = env_new;
	}
	else
	{
		if (env_new)
		{
			i = 0;
			while (env_new[i])
				free(env_new[i++]);
			free(env_new);
		}
	}
	check_arg_pwd(all);
}

/************************************
 * 		create_new_env_array		*
 * **********************************
*/
/* Start variables value:
 * 		create_new_env_array(all, tmp, i);
 *		all - pointer tomain structure;
 *		tmp - pointer to current list with command;
 *		i - number strings in all->env array;
 * Variables description, code comments:
 * 		char **env_new; future new env-array with new env variables.
 * Description:
 * 		The function counts the number of lines in the future array 
 * 		and allocates a memory area for it.
 * Return value:
 * 		Pointer to allocated memory area for new_env array with 
 * 		pointers to strings from old env array and void strings for
 * 		new variables from tmp->args.
 * Code comments:
 * 		---------------------
 * 		i = count_lines(all, tmp, "export", i, j);
 * 		counting the number of rows in the new array
 * 
 * 		env_new = (char **)malloc((i + 1) * sizeof(char *));// create new array
 * 		---------------------
 * 		env_new[i] = NULL;
 * 		NULL (nullify) the end of the new array
 * 		---------------------
 * 		while (all->env[++count])
 * 		fills the new array with lines from the old array
 * 
 * 		env_new[count] = all->env[count];
 * 		---------------------
 * Contains functions:
 * 		1. count_lines;
 * 		2. completion_code_malloc_error;
*/

char	**create_new_env_array(t_all *all, t_command *tmp, int i)
{
	int		count;
	char	**env_new;

	i = count_lines(all, tmp, "export", i);
	env_new = (char **)malloc((i + 1) * sizeof(char *));
	if (!env_new)
	{
		completion_code_malloc_error(NULL, "export with arguments");
		return (NULL);
	}
	env_new[i] = NULL;
	count = -1;
	while (all->env[++count])
		env_new[count] = all->env[count];
	env_new[count] = NULL;
	return (env_new);
}

/************************************
 * 			count_lines				*
 * **********************************
*/
/* Description:
 *		Determines the number of strings in the future env array.
 * Start variables value:
 * 		count_lines(all, "export", i, j);
 * Variables description, code comments:
 * 		Near instead all->nb_arg I write j.
 * 
 * 		int index; index of the string in env array
 *	
 *	1. while (tmp->args[++j])
 *		Until all the arguments in the argument array have been iterated over,
 *		the following actions are performed for each argument:
 *	
 *	1.1. if (!check_valid_args(tmp->args[j], oper_name, 1))
 *			continue;
 *			
 *		checks the validity of the entered arguments. If argument not validity
 *		print message about it and go to next argument.
 * 	1.2. if (check_double_args(&(tmp->args[j])))
 * 				continue;
 *  	checks for the presence of the same argument among subsequent arguments.
 * 		If argument is repeat among next arguments go to next argument 
 * 		(return 0 or 2, or 3).
 * 	1.3. index = find_env_str(all, oper_name, j, env);
 * 		find the env index of the string or null if env array don't contain
 * 		matching string.
 * 	1.4. if (!ft_strncmp(oper_name, "export", ft_strlen(oper_name)))
 * 		checks for which operation the function is applied:	export or unset.
 * 1.4.1. oper_name export.
 * 			if (all->env[index] == NULL)
 * 				++nb_env_lines;
 * 		If in 1.3. env array don't contain matching string, the future number
 * 		of lines in the new env array will increase.
 * 1.4.2. oper_name unset.
 * 			if (all->env[index])
 * 				--nb_env_lines;
 * 		If in 1.3. env array contain matching string, the future number of
 * 		lines in the new env array will decrease.
*/
/* Contains functions:
 * 		1. check_valid_args;
 * 			checks the validity of the entered arguments, 0/1 flag -
 * 			print / no message about the validity of the arguments
 * 		2. check_double_args;
 * 			checks for the presence of the same argument among subsequent
 * 			arguments 1 - repeats, 0 - no repeats
 * 		3. find_env_str;
 * 			find and return the env index of the string or null.
 * 		fibft. ft_strncmp;
 * 		fibft. ft_strlen;
*/

int	count_lines(t_all *all, t_command *tmp, char *oper_name, int nb_env_lines)
{
	int	index;

	all->nb_arg = -1;
	while (tmp->args[++all->nb_arg])
	{
		if (!check_valid_args(tmp->args[all->nb_arg], oper_name, 1))
			continue ;
		if (check_double_args(&(tmp->args[all->nb_arg]), 1))
			continue ;
		index = find_env_str(all, tmp, oper_name, all->env);
		if (!ft_strncmp(oper_name, "export", ft_strlen(oper_name)))
		{
			if (all->env[index] == NULL)
				++nb_env_lines;
		}
		else
		{
			if (all->env[index])
				--nb_env_lines;
		}
	}
	return (nb_env_lines);
}

/************************************
 * 		export_args_to_new_env		*
 * **********************************
*/
/* Start variables value:
 * 		export_args_to_new_env(all, tmp, env_new);
 * Description:
 * 			Add new variable to my env array or	overwrites existing env
 * 			variable with new value.
 * 			Change index i if function add new variable to my env array.
 * Code comments:
 * 		Near I write j instead all->nb_arg.
 * 		---------------------
 * 	1.	i_env_old = count_env_lines(all);
 * 	2.	while (tmp->args[++j] && g_completion_code == 0)
 * 		{
 * 	3.		if (!check_valid_args(tmp, "export", j, 0))
 * 				continue;
 * 			If argument not valid, go to next argument.
 * 
 * 	4.		if (check_double_args(&(tmp->args[j]), 0))
 * 				continue;
 * 		checks for the presence of the same argument among subsequent arguments.
 * 		If argument is repeat among next arguments go to next argument (return 1).
 * 		Check for '=' without plus.
 * 
 * 5.		i_env_new = find_env_str(all, tmp, "export", j, env_new);
 * 		Check if there is already such a variable in the new array:
 * 	5.1.	if (env_new[i_env_new])
 * 		Yes - complement it.
 * 			{
 * 				if (ft_strchr(tmp->args[j], '=') != NULL)// if sign '=' without '+'
 * 					change_env_str(all, tmp, i_env_new, env_new);
 * 			}
 * 	5.2.	else
 * 		No - create it.
 * 				create_env_str(all, tmp, env_new, &i_env_old);
 * 		}
 * 
 * Contains functions:
 * 		1. check_valid_args;
 * 			checks the validity of the entered arguments, 0/1 flag -
 * 			print / no message about the validity of the arguments
 * 		2. check_double_args;
 * 			checks for the presence of the same argument among subsequent
 * 			arguments 1 - repeats, 0 - no repeats
 * 		3. find_env_str;
 * 			find and return the env index of the string or null.
 * 		4. change_env_str;
 * 			overwrites existing env variable with new value.
 * 		fibft. ft_strdup;
 * 		fibft. ft_strchr;
*/

int	export_args_to_new_env(t_all *all, t_command *tmp, char **env_new)
{
	int		i_env_old;
	int		i_env_new;

	all->nb_arg = -1;
	i_env_old = count_env_lines(all);
	while (tmp->args[++all->nb_arg])
	{
		if (!check_valid_args(tmp->args[all->nb_arg], "export", 0))
			continue ;
		if (check_double_args(&(tmp->args[all->nb_arg]), 0))
			continue ;
		i_env_new = find_env_str(all, tmp, "export", env_new);
		if (env_new[i_env_new])
		{
			if (ft_strchr(tmp->args[all->nb_arg], '=') != NULL)
				if (change_env_str(all, tmp, i_env_new, env_new))
					return (1);
		}
		else if (create_env_str(all, tmp, env_new, &i_env_old))
			return (1);
	}
	return (0);
}
