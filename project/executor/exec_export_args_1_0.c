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
 * 			env_new[--i] = ft_strdup((*all->commands)->args[j]);
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
 * 
 * Contains functions:
 * 		1. count_lines;
 * 		2. export_args_to_new_env;
 * 			Add new variable to my env array or	overwrites existing env
 * 			variable with new value.
*/

void	subjoin_env(t_all *all, int i, int j)
{
	char 	**env_new;
	int		count;

	i = count_lines(all, "export", i, j);// подсчет количества строк в новом массиве
	env_new = (char **)malloc((i + 1) * sizeof(char *));// создание нового массива
	if (!env_new)
	{
		completion_code_malloc_error(NULL, "export with arguments");
		return ;
	}
	env_new[i] = NULL;// зануляю окончание нового массива
	count = -1;
	while (all->env[++count])// заполняю новый массив строками из старого массива
		env_new[count] = all->env[count];
	env_new[count] = NULL;
	export_args_to_new_env(all, j, env_new);// заполняю новый массив аргументами
	if (g_completion_code == 0)
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
 * 			count_lines				*
 * **********************************
*/
/* Description:
 *		Determines the number of strings in the future env array.
 * Start variables value:
 * 		count_lines(all, "export", i, j);
 * Variables description, code comments:
 * 		int index; index of the string in env array
 *	
 *	1. while ((*all->commands)->args[++j])
 *		Until all the arguments in the argument array have been iterated over,
 *		the following actions are performed for each argument:
 *	
 *	1.1. if (!check_valid_args(all, oper_name, j, 1))
 *			continue;
 *			
 *		checks the validity of the entered arguments. If argument not validity
 *		print message about it and go to next argument.
 * 	1.2. if (check_double_args(&((*all->commands)->args[j])))
 * 				continue;
 *  	checks for the presence of the same argument among subsequent arguments.
 * 		If argument is repeat among next arguments go to next argument.
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

int	count_lines(t_all *all, char *oper_name, int nb_env_lines, int j)
{
	int		index;
	
	while ((*all->commands)->args[++j])
	{
		if (!check_valid_args(all, oper_name, j, 1))
			continue;
		if (check_double_args(&((*all->commands)->args[j]), 1))
			continue;
		index = find_env_str(all, oper_name, j, all->env);
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
 * 		export_args_to_new_env(all, j, env_new);
 * Description:
 * 			Add new variable to my env array or	overwrites existing env
 * 			variable with new value.
 * 			Change index i if function add new variable to my env array.
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

void	export_args_to_new_env(t_all *all, int j, char **env_new)
{
	int		str_new_change;
	int		i_env_old;
	int		i_env_new;

	i_env_old = count_env_lines(all);
	while ((*all->commands)->args[++j] && g_completion_code == 0)
	{
		if (!check_valid_args(all, "export", j, 0))
			continue;
		if (check_double_args(&((*all->commands)->args[j]), 0))
			continue;// проверяю на последующее повторение аргумента с = без + (возврат 1)
		str_new_change = check_double_args(&((*all->commands)->args[j]), 1);// проверяю на последующее повторение аргумента с += (возврат 2) или без значения (возврат 3)
		i_env_new = find_env_str(all, "export", j, env_new);// 1) проверяю, есть ли уже такая переменная в новом массиве
		if (env_new[i_env_new])// да - дополняю ее
		{
			if (ft_strchr((*all->commands)->args[j], '=') != NULL)//если встретилось =
				change_env_str(all, j, i_env_new, env_new);
		}
		else// нет - создаю новую переменную
			create_env_str(all, j, env_new, &i_env_old);
	}
}

/************************************
 * 		check_valid_args			*
 * **********************************
*/
/* Variables description, code comments:
 * 		flag_print. 0/1 flag print/no message about the validity of the
 * 		arguments.
 * 		oper_name. Operation for wich the function is applied:	export or unset.
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
	if (((*all->commands)->args[j][i] == '+' && (*all->commands)->args[j][i + 1] == '=') ||
            (*all->commands)->args[j][i] == '=')
		return (print_not_valid((*all->commands)->args[j], oper_name, flag_print));
	while ((*all->commands)->args[j][i] != '\0')
	{
		if (((*all->commands)->args[j][i] == '=' && !ft_strncmp(oper_name, "export", 6)) ||
			((*all->commands)->args[j][i] == '+' && (*all->commands)->args[j][i + 1] == '=' && !ft_strncmp(oper_name, "export", 6)))
			break;
		if (!((*all->commands)->args[j][i] == '=' && !ft_strncmp(oper_name, "unset", 6)) &&
			(((*all->commands)->args[j][i] >= 'a' && (*all->commands)->args[j][i] <= 'z') ||
			((*all->commands)->args[j][i] >= 'A' && (*all->commands)->args[j][i] <= 'Z') ||
			((*all->commands)->args[j][i] >= '0' && (*all->commands)->args[j][i] <= '9' && i != 0) ||
             (*all->commands)->args[j][i] == '_'))
				++i;
		else
			return (print_not_valid((*all->commands)->args[j], oper_name, flag_print));
	}
	return (1);
}

/************************************
 * 		check_double_args			*
 * **********************************
*/
/* Description:
 * 		The function iterates over all subsequent arguments as long as there
 * 		are arguments or until the first match of a variable within an argument.
 * Return value:
 * 		If the desired variable is missing in subsequent arguments, the
 * 		function returns 0.
 * 		If the desired variable is found in the subsequent arguments, the
 * 		function returns 1.
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
