#include "../includes/minishell.h"

/****************************************
 * 		completion_code_malloc_error	*
 * **************************************
*/
/* Description:
 * 		In case if array_null point to NULL,
 * 		set value code_to_on to 1 and print 
 * 		error message.
 * Variables:
 * 		array_null. Array to compare with NULL.
 * 		code_to_on. Pointer to int variable to
 * 			change if array_nul is NULL.
 * 		open_name. The name of the operation 
 * 			that called malloc.
*/

void completion_code_malloc_error(int *code_to_on, char *array_null, char *open_name)
{
	if (array_null)
		return ;
	*code_to_on = 1;
	write(STDERR_FILENO, open_name, ft_strlen(open_name));
	write(STDERR_FILENO, ": malloc error. Try again.\n", 28);
}
