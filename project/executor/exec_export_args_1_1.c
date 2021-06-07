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
		write(STDOUT_FILENO, "minishell: ", 12);
		write(STDOUT_FILENO, operation_name, ft_strlen(operation_name));
		write(STDOUT_FILENO, ": `", 4);
		write(STDOUT_FILENO, args_name, ft_strlen(args_name));
		write(STDOUT_FILENO, "': not a valid identifier\n", 27);
	}
	all->completion_code = 1;
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

void	change_env_str(t_all *all, int j, int index)
{
	free(all->env[index]);
	all->env[index] = NULL;
	all->env[index] = ft_strdup(all->args[j]);
	completion_code_malloc_error(&all->completion_code, all->env[index], "export");
}
