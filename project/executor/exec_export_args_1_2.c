#include "minishell.h"

/*******************************************
 *     1.3.5.6.3.1.1.1.1. check_valid_args *
 * *****************************************
*/
/* Variables description, code comments:
 * 		flag_print. 0/1 flag print/no message about the validity of the
 * 		arguments.
 * 		oper_name. Operation for wich the function is applied:	export or unset.
 * Description:
 * 		checks the validity of the entered arguments (for command in current list).
 * Contains functions:
 * 		1.3.5.6.3.1.1.1.1.1. print_not_valid;
 * 			print message about not validity of the argument.
 * 		libft. ft_strncmp;
*/

int	check_valid_args(char *argj, char *oper_name, int flag_print)
{
	int		i;

	i = 0;
	if ((argj[i] == '+' && argj[i + 1] == '=') || argj[i] == '=')
		return (print_not_valid(argj, oper_name, flag_print));
	while (argj[i] != '\0')
	{
		if ((argj[i] == '=' && !ft_strncmp(oper_name, "export", 6))
			|| (argj[i] == '+' && argj[i + 1] == '='
				&& !ft_strncmp(oper_name, "export", 6)))
			break ;
		if (!(argj[i] == '=' && !ft_strncmp(oper_name, "unset", 6))
			&& ((argj[i] >= 'a' && argj[i] <= 'z')
				|| (argj[i] >= 'A' && argj[i] <= 'Z')
				|| (argj[i] >= '0' && argj[i] <= '9' && i != 0)
				|| argj[i] == '_'))
			++i;
		else
			return (print_not_valid(argj, oper_name, flag_print));
	}
	return (1);
}

/***************************************
 *  1.3.5.6.3.1.1.2. check_double_args *
 * *************************************
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
 * 		1.3.5.6.3.1.1.2.1. find_next_double_arg;
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

/************************************
 * 	1.3.5.6.3.3. check_arg_pwd  *
 * **********************************
*/
/* Description:
 * 		The function searches the (*all->commands)->args for a string
 * 		containing the PWD key. If all the keys found
 * 		without assigning or changing the values of the
 * 		PWD variable (without '=', without "+="), search
 * 		for the PWD variable in the my env-array, if
 * 		there is no symbol after the key '=' (end of line),
 * 		the PWD variable is assigned the value of the current
 * 		directory from all-pwd.
 *
 * Contains functions:
 * 		libft. ft_strncmp;
 * 		1.3.5.3.2. change_pwd;
*/

void	check_arg_pwd(t_all *all)
{
	int	i;
	int	cmp;

	i = 0;
	while ((*all->commands)->args[++i])
	{
		cmp = ft_strncmp((*all->commands)->args[i], "PWD", 3);
		if (!cmp && ((*all->commands)->args[i][3] == '='
			|| ((*all->commands)->args[i][3] == '+'
			&& (*all->commands)->args[i][4] == '=')))
			break ;
	}
	if ((*all->commands)->args[i] == NULL)
		i = get_my_env_index(all->env, "PWD", 3);
	if (all->env[i] && all->env[i][3] == '\0')
		change_pwd(all);
}
