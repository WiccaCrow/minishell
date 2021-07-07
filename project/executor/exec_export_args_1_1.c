#include "minishell.h"

/************************************
 * 			print_not_valid			*
 * **********************************
*/
/* Variables description, code comments:
 * 		args_name. Name of not validity argument.
 * 		flag_print. 0/1 flag print/no message about the validity of the
 * 			arguments.
 * 		oper_name. Operation for wich the function is applied:	export or unset.
 * Description:
 * 		Print message about validity of the entered arguments.
 * Contains functions:
 * 		libft. ft_strlen;
*/

int	print_not_valid(char *args_name, char *operation_name, int flag_print)
{
	if (flag_print)
	{
		write(STDERR_FILENO, "minishell: ", 12);
		write(STDERR_FILENO, operation_name, ft_strlen(operation_name));
		write(STDERR_FILENO, ": `", 4);
		write(STDERR_FILENO, args_name, ft_strlen(args_name));
		write(STDERR_FILENO, "': not a valid identifier\n", 27);
	}
	g_completion_code = 1;
	return (0);
}

/************************************
 * 			change_env_str			*
 * **********************************
*/
/* Description:
 * 		Changes the string in the array to the string from the argument:
 * 	1.	Frees the memory allocated for the string (all->env[index]) in my env
 * 		array.
 * 	2.	Sets the pointer from this line to the j argument
 * 		(tmp->args[j]).
*/

int	change_env_str(t_all *all, t_command *tmp, int index, char **env)
{
	char	*tmpp;

	tmpp = env[index];
	if (tmp->args[all->nb_arg][all->len_env_str] == '+')
	{
		if (env[index][all->len_env_str] == '=')
			env[index] = ft_strjoin(env[index],
					&tmp->args[all->nb_arg][all->len_env_str + 2]);
		else
			env[index] = ft_strjoin(env[index],
					&tmp->args[all->nb_arg][all->len_env_str + 1]);
	}
	else
		env[index] = ft_strdup(tmp->args[all->nb_arg]);
	completion_code_malloc_error(env[index], "export with arguments");
	if (env[index])
	{
		if (tmpp)
			free(tmpp);
		tmpp = NULL;
		return (0);
	}
	else
		env[index] = tmpp;
	return (1);
}

/************************************
 * 			find_env_str			*
 * **********************************
*/
/* Start variables value:
 * 		find_env_str(all, oper_name, env);
 * 			all->nb_arg is number of argument.
 * Variables description, code comments:
 *	1.	if (!ft_strncmp(oper_name, "unset", 5))
 * 			len_env_str = ft_strlen(tmp->args[all->nb_arg]);
 * 			If the function is called for command "unset", the length of the
 * 			part of the string being compared is equal to the length of the
 * 			argument.
 *  2.	else if (!ft_strncmp(oper_name, "export", 6) 
 * 		&& ft_strchr(tmp->args[all->nb_arg], '=') == NULL)
 * 		If command is unset and argument don't contain '=':
 *  2.1. len_env_str = ft_strlen(tmp->args[all->nb_arg]);
 * 		the length of the part of the string being compared is equal to the
 * 		length of the argument.
 *  3. else
 * 		len_env_str = ft_strchr(tmp->args[all->nb_arg], '=')
 * 			- tmp->args[all->nb_arg];
 * 		the length of the part of the string being compared is equal to the
 * 		length of the argument up to the letter '='
 * 	4. index = get_my_env_index(all->env, tmp->args[all->nb_arg],
 * 		len_env_str);
 * 		return (index);
 * 		Determines the index of the search string, if it exists in the array.
 * Description:
 *		Find and return the index of the string which contain variable from
 *		tmp->args[all->nb_arg] in the two-dimensional array my_env, if this
 *		variable is among all->env. Otherwise, it returns the index of the
 *		NULL row in the all->env array.
*/
/* Contains functions:
 * 		1. get_my_env_index;
 * 		Determines the index of the search string, if it exists in the array.
 * 		fibft. ft_strncmp;
 * 		fibft. ft_strlen;
 * 		fibft. ft_strchr;
*/

int	find_env_str(t_all *all, t_command *tmp, char *oper_name, char **env)
{
	size_t	len_env_str;
	int		index;
	char	c;

	if (!ft_strncmp(oper_name, "unset", 5))
		len_env_str = ft_strlen(tmp->args[all->nb_arg]);
	else if (!ft_strncmp(oper_name, "export", 6)
		&& ft_strchr(tmp->args[all->nb_arg], '=') == NULL)
		len_env_str = ft_strlen(tmp->args[all->nb_arg]);
	else
	{
		c = *(ft_strchr(tmp->args[all->nb_arg], '=') - 1);
		len_env_str = ft_strchr(tmp->args[all->nb_arg], '=')
			- tmp->args[all->nb_arg];
		if (c == '+')
			--len_env_str;
	}
	all->len_env_str = len_env_str;
	index = get_my_env_index(env, tmp->args[all->nb_arg], len_env_str);
	return (index);
}

/************************************
 * 		check_double_args			*
 * **********************************
*/
/* Description:
 * 		The function iterates over all subsequent arguments as long as there
 * 		are arguments, or:
 * 		1) until the first match of the variable in the argument if the
 * 			argument assigns a new value to the env-variable (before = no +).
 * 		2) if in the subsequent arguments there is no assignment of a new
 * 			value (= occurs only in the sequence + =), and the find_plus flag
 * 			is set (find_plus == 1) to check the addition of a new value
 * 			(before = is +), then until the first match of the variable in the
 * 			argument.
 * 		3) in other cases, it checks the character after the end of the
 * 			variable name (if the name continues, i.e. not 0, then another
 * 			variable with a similar beginning is specified in the checked
 * 			argument).
 * Return value:
 * 		If the desired variable is missing in subsequent arguments, the
 * 		function returns 0.
 * 		1) 1. If before = no +.
 * 		2) 2. If = occurs only in the sequence + =), and the flag of the
 * 			sequence check FLAG + = is also set.
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
				return (1);
			else if (find_plus && (args[nb_args][i] == '+'
				&& args[nb_args][i + 1] == '='))
				return (2);
			else if (find_plus && args[nb_args][i] == '\0')
				return (3);
		}
	}
	return (0);
}

/************************************
 * 			create_env_str			*
 * **********************************
*/
/* Description:
 * 		The function create a new string. If in argument after variable
 * 		followed the '+' '=' sequence, the new line will consist of the
 * 		variable name, the '=' symbol and the variable value that followed
 * 		the '+' '=' sequence.
 * Code comments:
 * 		while (tmp->args[all->nb_arg][all->len_env_str])
 * 		if I meet + =, I shift everything after + by 1 character to the left
 * Contains functions:
 * 		completion_code_malloc_error;
 * 		fibft. ft_strdup;
 * 		fibft. ft_strchr;
*/

int	create_env_str(t_all *all, t_command *tmp, char **env, int *i)
{
	if (tmp->args[all->nb_arg][all->len_env_str] == '+')
	{
		while (tmp->args[all->nb_arg][all->len_env_str])
		{
			tmp->args[all->nb_arg][all->len_env_str]
				= tmp->args[all->nb_arg][all->len_env_str + 1];
			++all->len_env_str;
		}
	}
	env[*i] = ft_strdup(tmp->args[all->nb_arg]);
	if (env[*i] == NULL)
	{
		completion_code_malloc_error(NULL, "export with arguments");
		return (1);
	}
	env[++(*i)] = NULL;
	return (0);
}
