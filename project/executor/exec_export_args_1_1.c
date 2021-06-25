#include "../includes/minishell.h"

/************************************
 * 			print_not_valid			*
 * **********************************
*/
/* Variables description, code comments:
 * 		args_name. Name of not validity argument.
 * 		flag_print. 0/1 flag print/no message about the 
 * 			validity of the arguments.
 * 		oper_name. 	Operation for wich the function is applied:
 * 			export or unset.
 * Description:
 * 		Print message about validity of the entered arguments.
 * Contains functions:
 * 		libft. ft_strlen;
*/

int	print_not_valid(t_all *all, char *args_name, char *operation_name, int flag_print)
{
	if (flag_print)
	{
		write((*(all->commands))->output_fd, "minishell: ", 12);
		write((*(all->commands))->output_fd, operation_name, ft_strlen(operation_name));
		write((*(all->commands))->output_fd, ": `", 4);
		write((*(all->commands))->output_fd, args_name, ft_strlen(args_name));
		write((*(all->commands))->output_fd, "': not a valid identifier\n", 27);
	}
    g_completion_code = 1;
	return (0);
}

/************************************
 * 			change_env_str			*
 * **********************************
*/ 
/* Description:
 * 		Changes the string in the array to the string from the 
 * 		argument:
 * 	1.	Frees the memory allocated for the string 
 * 		(all->env[index]) in my env array.
 * 	2.	Sets the pointer from this line to the j argument
 * 		(all->args[j]).
*/

void	change_env_str(t_all *all, int j, int index, char **env)
{
	char	*tmp;

	tmp = env[index];
	if (all->args[j][all->len_env_str] == '+')
	{
		if (env[index][all->len_env_str] == '=')
			env[index] = ft_strjoin(env[index], &all->args[j][all->len_env_str + 2]);
		else
			env[index] = ft_strjoin(env[index], &all->args[j][all->len_env_str + 1]);
	}
	else
		env[index] = ft_strdup(all->args[j]);
	completion_code_malloc_error(env[index], "export with arguments");
	if (g_completion_code == 0)
	{
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
	else
		env[index] = tmp;
}

/************************************
 * 			find_env_str			*
 * **********************************
*/
/* Start variables value:
 * 		find_env_str(all, oper_name, j, env);
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

int	find_env_str(t_all *all, char *oper_name, int j, char **env)
{
	size_t	len_env_str;
	int		index;
	char	c;

	if (!ft_strncmp(oper_name, "unset", 5))
		len_env_str = ft_strlen(all->args[j]);
	else if (!ft_strncmp(oper_name, "export", 6) && ft_strchr(all->args[j], '=') == NULL)
		len_env_str = ft_strlen(all->args[j]);
	else
	{
		c = *(ft_strchr(all->args[j], '=') - 1);
		len_env_str = ft_strchr(all->args[j], '=') - all->args[j];
		if (c == '+')
			--len_env_str;
	}
	all->len_env_str = len_env_str;
	index = get_my_env_index(env, all->args[j], len_env_str);
	return (index);
}

/************************************
 * 		check_double_args			*
 * **********************************
*/
/* Description:
 * 		The function iterates over all subsequent 
 * 		arguments as long as there are arguments, or:
 * 		1) until the first match of the variable in the 
 * 			argument if the argument assigns a new value 
 * 			to the env-variable (before = no +).
 * 		2) if in the subsequent arguments there is no 
 * 			assignment of a new value (= occurs only in 
 * 			the sequence + =), and the find_plus flag is 
 * 			set (find_plus == 1) to check the addition 
 * 			of a new value (before = is +), then until 
 * 			the first match of the variable in the 
 * 			argument.
 * 		3) in other cases, it checks the character after 
 * 			the end of the variable name (if the name 
 * 			continues, i.e. not 0, then another variable 
 * 			with a similar beginning is specified in the 
 * 			checked argument).
 * Return value:
 * 		If the desired variable is missing in subsequent 
 * 		arguments, the function returns 0.
 * 		1) 1. If before = no +.
 * 		2) 2. If = occurs only in the sequence + =), and 
 * 			the flag of the sequence check FLAG + = is also 
 * 			set.
 * 		3) 3. if the argument is over.
 * Contains functions:
 * 		libft. ft_strncmp;
*/

int	find_next_double_arg(char **args, int find_plus, int nb_args, int i)
{
	while (args[++nb_args])
	{
		if (!ft_strncmp(args[0], args[nb_args], i))
		{
			if (args[nb_args][i] == '=')
				return (1);// если среди последующих аргументов есть =
			else if (find_plus && (args[nb_args][i] == '+' && args[nb_args][i + 1] == '='))
				return (2);// если среди последующих аргументов есть +=
			else if (find_plus && args[nb_args][i] == '\0')
				return (3);// если среди последующих аргументов есть аргумент без значения и без =
		}
	}
	return (0);// если аргумент больше не повторяется
}

/************************************
 * 			create_env_str			*
 * **********************************
*/
/* Description:
 * 		The function create a new string.
 * 		If in argument after variable followed the '+' 
 * 		'=' sequence, the new line will consist of the 
 * 		variable name, the '=' symbol and the variable 
 * 		value that followed the '+' '=' sequence.
 * Contains functions:
 * 		completion_code_malloc_error;
 * 		fibft. ft_strdup;
 * 		fibft. ft_strchr;
*/

void	create_env_str(t_all *all, int j, char **env, int *i)
{
	if (all->args[j][all->len_env_str] == '+')
	{
		while (all->args[j][all->len_env_str])// если я встретила +=, смещаю все после + на 1 символ влево
		{
			all->args[j][all->len_env_str] = all->args[j][all->len_env_str + 1];
			++all->len_env_str;
		}
	}
	env[*i] = ft_strdup(all->args[j]);
	if (env[*i] == NULL)
		completion_code_malloc_error(NULL, "export with arguments");
	env[++(*i)] = NULL;
}
