#include "../includes/minishell.h"

/************************************
 * 				subjoin_env			*
 * **********************************
*/
/* Start variables value:
 * 		subjoin_env(all, i, -1);
 * Variables description, code comments:
 * 		char **env_new; future new env-array with 
 * 								new env variables.
 * 		int index; the index of the search string 
 * 						 in the current env array.
 * 		if (all->env[index] == NULL)
 * 			env_new[--i] = ft_strdup(all->args[j]);
 * 			//if in the env array was no such 
 * 			// variable, create it.
 * Description:
 * 		The export command allow parameters and 
 * 		functions to be added to and deleted from the 
 * 		environment. If the value of a parameter in 
 * 		the environment is modified, the new value 
 * 		becomes part of the environment, replacing the 
 * 		old. 
 * 		The environment inherited by any executed 
 * 		command consists of the shell’s initial 
 * 		environment, whose values may be modified in 
 * 		the shell, less any pairs removed by the unset 
 * 		command, plus any additions via the export 
 * 		command.
 * 
 * Contains functions:
 * 		1. count_lines;
 * 		2. export_args_to_new_env;
 * 			Add new variable to my env array or
 * 			overwrites existing env variable with new 
 * 			value.
*/

void	subjoin_env(t_all *all, int i, int j)
{
	char 	**env_new;

	i = count_lines(all, "export", i, j);
	env_new = (char **)malloc((i + 1) * sizeof(char *));
	env_new[i] = NULL;
	if (!env_new)
	{
		completion_code_malloc_error(&(all->completion_code), NULL, "export with arguments");
		return ;
	}
	export_args_to_new_env(all, j, env_new, &i);
	if (all->completion_code == 0)
	{
		while (--i >= 0)
			env_new[i] = all->env[i];
		free(all->env);
		all->env = env_new;
	}
	else
		free(env_new);
}

/************************************
 * 			count_lines				*
 * **********************************
*/
/* Description:
 *		Determines the number of strings in the 
 *		future env array.
 * Start variables value:
 * 		count_lines(all, "export", i, j);
 * Variables description, code comments:
 * 	int index; index of the string in env array
 *	
 *	1. while (all->args[++j])
 *		Until all the arguments in the argument array 
 *		have been iterated over, the following actions 
 *		are performed for each argument:
 *	
 *	1.1. if (!check_valid_args(all, oper_name, j, 1))
 *			continue;
 *			
 *		checks the validity of the entered arguments. 
 * 		if argument not validity print message about it and 
 * 		go to next argument.
 * 	1.2. if (check_double_args(&(all->args[j])))
 * 				continue;
 *  	checks for the presence of the same argument among 
 * 		subsequent arguments.
 * 		If argument is repeat among next arguments go to 
 * 		next argument.
 * 	1.3. index = find_env_str(all, oper_name, j);
 * 		find the env index of the string or null if env array
 * 		don't contain matching string.
 * 	1.4. if (!ft_strncmp(oper_name, "export", ft_strlen(oper_name)))
 * 		checks for which operation the function is applied:
 * 		export or unset.
 * 1.4.1. oper_name export.
 * 			if (all->env[index] == NULL)
 * 				++nb_env_lines;
 * 		If in 1.3. env array don't contain matching string, 
 * 		the future number of lines in the new env array will 
 * 		increase.
 * 1.4.2. oper_name unset.
 * 			if (all->env[index])
 * 				--nb_env_lines;
 * 		If in 1.3. env array contain matching string, 
 * 		the future number of lines in the new env array will 
 * 		decrease.
*/
/* Contains functions:
 * 		1. check_valid_args;
 * 			checks the validity of the entered arguments, 
 * 			0/1 flag - print / no message about the 
 * 			validity of the arguments
 * 		2. check_double_args;
 * 			checks for the presence of the same argument 
 * 			among subsequent arguments 1 - repeats, 
 * 			0 - no repeats
 * 		3. find_env_str;
 * 			find and return the env index of the string 
 * 			or null.
 * 		fibft. ft_strncmp;
 * 		fibft. ft_strlen;
*/

int	count_lines(t_all *all, char *oper_name, int nb_env_lines, int j)
{
	int		index;
	
	while (all->args[++j])
	{
		if (!check_valid_args(all, oper_name, j, 1))
			continue;
		if (check_double_args(&(all->args[j]), 1))
			continue;
printf("args[j] = %s\n", all->args[j]);
		index = find_env_str(all, oper_name, j);
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
printf("nb_env_lines = %d\n", nb_env_lines);
	return (nb_env_lines);
}

/************************************
 * 		export_args_to_new_env		*
 * **********************************
*/
/* Start variables value:
 * 		export_args_to_new_env(all, j, env_new, &i);
 * Description:
 * 			Add new variable to my env array or
 * 			overwrites existing env variable with new 
 * 			value.
 * 			Change index i if function add new 
 * 			variable to my env array.
 * 
 * Contains functions:
 * 		1. check_valid_args;
 * 			checks the validity of the entered arguments, 
 * 			0/1 flag - print / no message about the 
 * 			validity of the arguments
 * 		2. check_double_args;
 * 			checks for the presence of the same argument 
 * 			among subsequent arguments 1 - repeats, 
 * 			0 - no repeats
 * 		3. find_env_str;
 * 			find and return the env index of the string 
 * 			or null.
 * 		4. change_env_str;
 * 			overwrites existing env variable with new 
 * 			value.
 * 		fibft. ft_strdup;
 * 		fibft. ft_strchr;
*/

void	export_args_to_new_env(t_all *all, int j, char **env_new, int *i)
{
	int		index;
	int		str_new_change;

	while (all->args[++j] && all->completion_code == 0)
	{
		if (!check_valid_args(all, "export", j, 0))
			continue;
		str_new_change = check_double_args(&(all->args[j]), 0);
		if (str_new_change)
			continue;
		index = find_env_str(all, "export", j);
		if (all->env[index] == NULL && str_new_change == 1)
		{
			if (all->args[j][all->len_env_str--] == '+')
			{
				while (all->args[j][++all->len_env_str])
					all->args[j][all->len_env_str] = all->args[j][all->len_env_str + 1];
			}
			env_new[--(*i)] = ft_strdup(all->args[j]);
			if (env_new[*i] == NULL)
				completion_code_malloc_error(&(all->completion_code), NULL, "export with arguments");
		}
		else
		{
			if (ft_strchr(all->args[j], '=') != NULL)
				change_env_str(all, j, index);
		}
	}
}

/************************************
 * 		check_valid_args			*
 * **********************************
*/
/* Variables description, code comments:
 * 		flag_print. 0/1 flag print/no message about the 
 * 			validity of the arguments.
 * 		oper_name. 	Operation for wich the function is applied:
 * 			export or unset.
 * Description:
 * 		checks the validity of the entered arguments.
 * Contains functions:
 * 		print_not_valid;
 * 			print message about not validity of the argument.
 * 		libft. ft_strncmp;
*/

int	check_valid_args(t_all *all, char *oper_name, int j, int flag_print)
{
	int		i;

	i = 0;
	while (all->args[j][i] != '\0')
	{
		if ((all->args[j][i] == '=' && !ft_strncmp(oper_name, "export", 6)) ||
			(all->args[j][i] == '+' && all->args[j][i + 1] == '=' && !ft_strncmp(oper_name, "export", 6)))
			break;
		if (!(all->args[j][i] == '=' && !ft_strncmp(oper_name, "unset", 6)) &&
			((all->args[j][i] >= 'a' && all->args[j][i] <= 'z') ||
			(all->args[j][i] >= 'A' && all->args[j][i] <= 'Z') ||
			(all->args[j][i] >= '0' && all->args[j][i] <= '9' && i != 0) ||
			all->args[j][i] == '_'))
				++i;
		else
			return (print_not_valid(all, all->args[j], oper_name, flag_print));
	}
	return (1);
}

/************************************
 * 		check_double_args			*
 * **********************************
*/
/* Description:
 * 		The function iterates over all subsequent arguments 
 * 		as long as there are arguments or until the first 
 * 		match of a variable within an argument.
 * Return value:
 * 		If the desired variable is missing in subsequent 
 * 		arguments, the function returns 0.
 * 		If the desired variable is found in the subsequent 
 * 		arguments, the function returns 1.
 * Contains functions:
 * 		find_next_double_arg;
 * 		libft. ft_strchr;
 * 		libft. ft_strlen;
*/

int	check_double_args(char **args, int find_plus)
{
	int		i;
	int		nb_args;
	char	*tmp;

	i = 0;
	tmp = ft_strchr(args[0], '=');
	if (tmp)
	{
		i = tmp - args[0];
		if (args[0][i - 1] == '+')
			--i;
	}
	else
		i = ft_strlen(args[0]);
	nb_args = 0;
	return (find_next_double_arg(args, find_plus, nb_args, i));
}
