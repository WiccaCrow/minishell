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

void	print_export(t_all *all, char **sort_env_index)
{
	int		i;
	char	*len_equal;

	i = -1;
	while (sort_env_index[++i])
	{
		write((*all->commands)->output_fd, "declare -x ", ft_strlen("declare -x "));
		len_equal = ft_strchr(sort_env_index[i], '=');
		if (len_equal++)
		{
			write((*all->commands)->output_fd, sort_env_index[i], len_equal - sort_env_index[i]);
			write((*all->commands)->output_fd, "\"", 1);
			write((*all->commands)->output_fd, len_equal, ft_strlen(len_equal));
			write((*all->commands)->output_fd, "\"\n", 2);
		}
		else
		{
			write((*all->commands)->output_fd, sort_env_index[i], ft_strlen(sort_env_index[i]));
			write((*all->commands)->output_fd, "\n", 1);
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
