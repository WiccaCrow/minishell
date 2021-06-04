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
 * 		2. check_valid_args;
 * 			checks the validity of the entered arguments, 
 * 			0/1 flag - print / no message about the 
 * 			validity of the arguments
 * 		3. check_double_args;
 * 			checks for the presence of the same argument 
 * 			among subsequent arguments 1 - repeats, 
 * 			0 - no repeats
 * 		4. find_env_str;
 * 			find and return the env index of the string 
 * 			or null.
 * 		5. change_env_str;
 * 			overwrites existing env variable with new 
 * 			value.
 * 		fibft. ft_strdup;
 * 		fibft. ft_strchr;
*/

void	subjoin_env(t_all *all, int i, int j)
{
	char 	**env_new;
	int		index;

	i = count_lines(all, "export", i, j);
	env_new = (char **)malloc((i + 1) * sizeof(char *));
	env_new[i] = NULL;
	while (all->args[++j])
	{
		if (!check_valid_args(all, "export", j, 0))
			continue;
		if (check_double_args(&(all->args[j])))
			continue;
		index = find_env_str(all, "export", j);
		if (all->env[index] == NULL)
			env_new[--i] = ft_strdup(all->args[j]);
		else
		{
			if (ft_strchr(all->args[j], '=') != NULL)
				change_env_str(all, j, index);
		}
	}
	while (--i >= 0)
		env_new[i] = all->env[i];
	free(all->env);
	all->env = env_new;
}

/************************************
 * 			count_lines				*
 * **********************************
*/

/* Description:
 *		Determines the number of strings in the 
 *		future E array.
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
		if (check_double_args(&(all->args[j])))
			continue;
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
	return (nb_env_lines);
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
		if (all->args[j][i] == '=' && !ft_strncmp(oper_name, "export", 6))
			break;
		if (!(all->args[j][i] == '=' && !ft_strncmp(oper_name, "unset", 6)) &&
			((all->args[j][i] >= 'a' && all->args[j][i] <= 'z') ||
			(all->args[j][i] >= 'A' && all->args[j][i] <= 'Z') ||
			(all->args[j][i] >= '0' && all->args[j][i] <= '9' && i != 0) ||
			all->args[j][i] == '_'))
				++i;
		else
			return (print_not_valid(all->args[j], oper_name, flag_print));
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
 * 		libft. ft_strncmp;
*/

int	check_double_args(char **args)
{
	int	i;
	int	nb_args;

	i = 0;
	while (args[0][i] != '=' && args[0][i])
		++i;
	nb_args = 0;
	while (args[++nb_args])
	{
		if (!ft_strncmp(args[0], args[nb_args], i))
		{
			if (args[nb_args][i] == '=' || args[nb_args][i] == '\0')
				return (1);
		}
	}
	return (0);
}

/************************************
 * 			find_env_str			*
 * **********************************
*/

/* Start variables value:
 * 		find_env_str(all, oper_name, j);
 * 			j is number of argument.
 * Variables description, code comments:
 *	1.	if (!ft_strncmp(oper_name, "unset", 5))
 * 			len_env_str = ft_strlen(all->args[j]);
 * 			If the function is called for command 
 * 			"unset", the length of the part of the 
 * 			string being compared is equal to the 
 * 			length of the argument.
 *  2.	else if (!ft_strncmp(oper_name, "export", 6) 
 * 		&& ft_strchr(all->args[j], '=') == NULL)
 * 		If command is unset and argument don't contain '=':
 *  2.1. len_env_str = ft_strlen(all->args[j]);
 * 		the length of the part of the string being 
 * 		compared is equal to the length of the argument.
 *  3. else
 * 		len_env_str = ft_strchr(all->args[j], '=') 
 * 			- all->args[j];
 * 		the length of the part of the string being 
 * 		compared is equal to the length of the argument 
 * 		up to the letter '='
 * 	4. index = get_my_env_index(all->env, all->args[j], 
 * 		len_env_str);
 * 		return (index);
 * 		Determines the index of the search string, if it 
 * 		exists in the array.
 * Description:
 *		Find and return the index of the string which 
 * 		contain variable from all->args[j] in the 
 * 		two-dimensional array my_env, if this variable
 * 		is among all->env. Otherwise, it returns the 
 * 		index of the NULL row in the all->env array.
*/

/* Contains functions:
 * 		1. get_my_env_index;
 * 			Determines the index of the search string, 
 * 			if it exists in the array.
 * 		fibft. ft_strncmp;
 * 		fibft. ft_strlen;
 * 		fibft. ft_strchr;
*/

int	find_env_str(t_all *all, char *oper_name, int j)
{
	size_t	len_env_str;
	int		index;

	if (!ft_strncmp(oper_name, "unset", 5))
		len_env_str = ft_strlen(all->args[j]);
	else if (!ft_strncmp(oper_name, "export", 6) && ft_strchr(all->args[j], '=') == NULL)
		len_env_str = ft_strlen(all->args[j]);
	else
		len_env_str = ft_strchr(all->args[j], '=') - all->args[j];
	index = get_my_env_index(all->env, all->args[j], len_env_str);
	return (index);
}
