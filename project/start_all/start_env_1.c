#include "minishell.h"

/************************************
 *  1.7.1.3.1. init_env_av0_path    *
 * **********************************
*/
/* Description:
 *       The function takes the name of the running program with path (example
 *       "path/minishell") and fills the variable *av0_path with the path to
 *       this program (example *av0_path = "path").
 * 	Accepted variables:
 * 		char **av0_path. It is passed to this function as &av0_path_var
 * 				(from char *av0_path_var).
 * Contains functions:
 * 		libft.  ft_strlen;
 * 		1.7.1.2.init_env_err_with_exit_msh;
 * 		libft.  ft_strncmp;
 */

void	init_env_av0_path(t_all *all, char *av0, char **av0_path)
{
	int	av_len;

	av_len = ft_strlen(av0);
	while (av_len && '/' != av0[av_len - 1])
		--av_len;
	*av0_path = (char *)malloc(sizeof(char) * (av_len + 1));
	init_env_err_with_exit_msh(all, *av0_path, "minishell: init_env");
	(*av0_path)[av_len] = '\0';
	while (av_len--)
		(*av0_path)[av_len] = av0[av_len];
	av_len = ft_strlen(*av0_path);
	if (!ft_strncmp(*av0_path, "./", av_len))
	{
		free(*av0_path);
		(*av0_path) = getcwd(NULL, 0);
	}
	else
		(*av0_path)[av_len - 1] = '\0';
}

/*****************************************
 * 1.7.1.3.2. init_env_path_without_path *
 * ***************************************
*/
/* Description:
 *       The function create and fill env variable PATH
 *       "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.:" and path to the
 *       minishell (income av0_path)after last char ':'.
 *       And set it on all->env[i].
 * Contains functions:
 * 		1.7.1.2. init_env_err_with_exit_msh;
 * 		libft.   ft_strjoin;
 */

void	init_env_path_without_path(t_all *all, char *av0_path, int i)
{
	char	*new_path;

	new_path = ft_strjoin(
			"PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.:", av0_path);
	ft_free((void **)&av0_path);
	init_env_err_with_exit_msh(all, new_path, "minishell: init_env");
	all->env[i] = new_path;
}

/****************************************
 *   1.7.1.3.3. init_env_path_with_path *
 * **************************************
*/
/* Description:
 *       The function checks if there is a path in the av0_path variable among
 *       the paths specified in the PATH variable in env.
 *       If av0_path is absent among the paths in PATH, add it through the ':
 *       symbol.
 * Contains functions:
 * 		1.7.1.3.3.1. init_env_path_split;
 * 		1.7.1.3.3.2. free_char_array;
 * 		1.7.1.2. init_env_err_with_exit_msh;
 * 		libft.   ft_strlen;
 * 		libft.   ft_split;
 * 		libft.   ft_free;
 * 		libft.   ft_strncmp;
 * 		libft.   ft_strjoin;
 */

void	init_env_path_with_path(t_all *all, char *av0_path, int index_path)
{
	char	*tmp;
	int		j;

	j = init_env_path_split(all, index_path, av0_path);
	if (NULL == all->path_split[j])
	{
		tmp = ft_strjoin(all->env[index_path], ":");
		if (NULL == tmp)
		{
			free_char_array(all->path_split);
			ft_free((void **)&av0_path);
			init_env_err_with_exit_msh(all, NULL, "minishell: init_env");
		}
		tmp = gnl_strjoin(tmp, av0_path);
		ft_free((void **)&av0_path);
		init_env_err_with_exit_msh(all, tmp, "msh: init_env");
		free(all->env[index_path]);
		all->env[index_path] = tmp;
	}
	free_char_array(all->path_split);
}

/*************************************
 *  1.7.1.3.3.1. init_env_path_split *
 * ***********************************
*/
/* Description:
 * 		The function split PATH on paths to all->path_split.
 * 		Checks if there is a path in the av0_path variable among
 * 		the all->path_split strings.
 * 		And returns its index in all->path_split.
 * Return value:
 * 		If among the rows in PATH there is av0_path, the index 
 * 		of this string in the array is returned.
 * 		If among the rows in PATH there is no av0_path, the 
 * 		index of the NULL string in the array is returned.
 * Contains functions:
 * 		1.7.1.2. init_env_err_with_exit_msh;
 * 		libft.   ft_strlen;
 * 		libft.   ft_split;
 * 		libft.   ft_free;
 * 		libft.   ft_strncmp;
 */

int	init_env_path_split(t_all *all, int index_path, char *av0_path)
{
	int		av_len;
	int		j;

	av_len = ft_strlen(av0_path);
	all->path_split = ft_split(all->env[index_path], ':');
	if (NULL == all->path_split)
	{
		ft_free((void **) &av0_path);
		init_env_err_with_exit_msh(all, NULL, "minishell: init_env");
	}
	j = -1;
	while (all->path_split[++j])
		if (0 == ft_strncmp(av0_path, all->path_split[j], av_len))
			break ;
	return (j);
}
