#include "minishell.h"

/************************************
 * 		init_env_av0_path     		*
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
 * 		ft_strlen;
 * 		init_env_err_with_exit_msh;
 * 		ft_strncmp;
 */

void	init_env_av0_path(t_all *all, char *av0, char **av0_path)
{
	int	av_len;

	av_len = ft_strlen(av0);
	while (av_len && '/' != av0[av_len - 1])
		--av_len;
	if (!av_len)
		return ;
	*av0_path = (char *)malloc(sizeof(char) * (av_len + 1));
	init_env_err_with_exit_msh(all, *av0_path, "minishell: init_env");
	(*av0_path)[av_len] = '\0';
	while (av_len--)
		(*av0_path)[av_len] = av0[av_len];
	av_len = ft_strlen(*av0_path);
	if (!ft_strncmp(*av0_path, "./", av_len))
		(*av0_path) = getcwd(NULL, 0);
	else
		(*av0_path)[av_len - 1] = '\0';
}

/************************************
 * 	init_env_path_without_path   	*
 * **********************************
*/
/* Description:
 *       The function create and fill env variable PATH
 *       "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.:" and path to the
 *       minishell (income av0_path)after last char ':'.
 *       And set it on all->env[i].
 * Contains functions:
 * 		init_env_err_with_exit_msh;
 * 		ft_strjoin;
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

/************************************
 * 		init_env_path_with_path   	*
 * **********************************
*/
/* Description:
 *       The function checks if there is a path in the av0_path variable among
 *       the paths specified in the PATH variable in env.
 *       If av0_path is absent among the paths in PATH, add it through the ':
 *       symbol.
 * Contains functions:
 * 		init_env_err_with_exit_msh;
 * 		ft_strlen;
 * 		ft_split;
 * 		ft_free;
 * 		ft_strncmp;
 * 		ft_strjoin;
 */

void	init_env_path_with_path(t_all *all, char *av0_path, int index_path,
								int j)
{
	int		av_len;
	char	**path_split;

	av_len = ft_strlen(av0_path);
	path_split = ft_split(all->env[index_path], ':');
	if (NULL == path_split)
		ft_free((void **)&av0_path);
	if (NULL == path_split)
		init_env_err_with_exit_msh(all, NULL, "minishell: init_env");
	while (path_split[++j])
		if (0 == ft_strncmp(av0_path, path_split[j], av_len))
			break ;
	if (NULL == path_split[j])
	{
		all->env[index_path] = ft_strjoin(all->env[index_path], ":");
		if (NULL == all->env[index_path])
		{
			free_char_array(path_split);
			ft_free((void **)&av0_path);
			init_env_err_with_exit_msh(all, NULL, "minishell: init_env");
		}
		all->env[index_path] = ft_strjoin(all->env[index_path], av0_path);
		ft_free((void **)&av0_path);
		init_env_err_with_exit_msh(all, all->env[index_path], "msh: init_env");
	}
	free_char_array(path_split);
}
