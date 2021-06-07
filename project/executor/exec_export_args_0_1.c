#include "../includes/minishell.h"

/************************************
 * 			free_sort_index			*
 * **********************************
*/
/* Description:
 * 		Print ready sort array.
 * Contains functions:
 * 		libft. ft_strlen;
 * 		libft. ft_strchr;
*/

void	print_export(char **sort_env_index)
{
	int		i;
	char	*len_equal;

	i = -1;
	while (sort_env_index[++i])
	{
		write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
		len_equal = ft_strchr(sort_env_index[i], '=');
		if (len_equal++)
		{
			write(STDOUT_FILENO, sort_env_index[i], len_equal - sort_env_index[i]);
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, len_equal, ft_strlen(len_equal));
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
		{
			write(STDOUT_FILENO, sort_env_index[i], ft_strlen(sort_env_index[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}

/************************************
 * 			free_sort_index			*
 * **********************************
*/
/* Description:
 * 		Free array of sort index.
*/

void	free_sort_index(char **sort_env_index, int *sort)
{
	if (sort)
	{
		free(sort);
		sort = NULL;
	}
	if (**sort_env_index)
	{
		free(sort_env_index);
		sort_env_index = NULL;
	}
}
