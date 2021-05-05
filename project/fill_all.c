#include "./includes/minishell.h"

/************************************
 * 		1.3. fill_all				*
 * **********************************
 * This function performs several important operations:
 * 	1) checks the validity of the data entered
 * 		by the user into the shell command line,
 * 		sets the data validity flag in the t_all
 * 		structure.
 * 				flag:		1 - data is not valid.
 * 	2) based on these data, fills in the main
 * 		structure of the program. t_all all.
*/

void	fill_all(t_all *all)
{
    int	ret;

    ret = 1;
//	while (ret != -1)
//	{
    ret = get_next_line(1, &all->line);
    parser(all);
    executor(all);
//	}
}