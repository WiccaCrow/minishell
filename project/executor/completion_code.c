#include "minishell.h"

/**************************************************
 *   1.3.5.6.3.1.2. completion_code_malloc_error  *
 * ************************************************
*/
/* Description:
 * 		In case if array_null point to NULL, set value code_to_on to 1 
 * 		and print error message.
 * Variables:
 * 		array_null. Array to compare with NULL.
 * 		g_completion_code. set 1 if array_nul is NULL.
 * 		oper_name. The name of the operation that called malloc.
*/

void	completion_code_malloc_error(char *array_null, char *oper_name)
{
	if (array_null)
		return ;
	g_completion_code = 1;
	write(STDERR_FILENO, oper_name, ft_strlen(oper_name));
	write(STDERR_FILENO, ": malloc error. Try again.\n", 28);
}

/****************************************
 * 		completion_code_int_ret_error	*
 * **************************************
*/
/* Description:
 * 		The function can be used if errno is set to the 
 * 		appropriate value when your function fails.
 * Variables:
 * 		oper_name is the name of the operation in which the 
 * 			error occurred (example, "minishell: pipes: ").
 * 		g_completion_code will be set to error_code.
*/

void	completion_code_int_ret_error(char *oper_name, int error_code)
{
	char	*err;

	write(STDERR_FILENO, oper_name, ft_strlen(oper_name));
	err = strerror (errno);
	write(STDERR_FILENO, err, ft_strlen(err));
	write(STDERR_FILENO, "\n", 1);
	g_completion_code = error_code;
}

/****************************************
 * 		completion_code_fork_error		*
 * **************************************
*/
/* Description:
 * 		The function print error message.
 * Variables:
 * 		oper_name is the name of the operation in which the 
 * 			error occurred (example, "minishell: pipes: ").
 * 		g_completion_code will be set to error_code.
 * Return value:
 * 		-1.
*/

int	completion_code_fork_error(char *oper_name, char *err_text, int error_code)
{
	write(STDERR_FILENO, oper_name, ft_strlen(oper_name));
	write(STDERR_FILENO, err_text, ft_strlen(err_text));
	g_completion_code = error_code;
	return (-1);
}
