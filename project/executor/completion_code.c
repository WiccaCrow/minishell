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
 * 		g_completion_code. set 1 if array_nul
 * 		    is NULL.
 * 		open_name. The name of the operation 
 * 			that called malloc.
*/

void completion_code_malloc_error(char *array_null, char *open_name)
{
	if (array_null)
		return ;
    g_completion_code = 1;
	write(STDERR_FILENO, open_name, ft_strlen(open_name));
	write(STDERR_FILENO, ": malloc error. Try again.\n", 28);
}
