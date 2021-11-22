#include "minishell.h"

/************************************
 * 		1.7.1. init_env     		*
 * **********************************
*/
/* Description:
 *       do copy env;
 * 		Function add OLDPWD and add PWD with 
 * 		real pwd value if env don't contain 
 * 		PWD or OLDPWD.
 * 		The function in init_env_path_msh_dir() fills the PATH variable
 * 		depending on the passed value of this variable to the minishell.
 * 		For more details see the description of the function
 * 		init_env_path().
 * Contains functions:
 * 		1.7.1.1. init_env_allocate_memory;
 * 		1.7.1.2. init_env_err_with_exit_msh;
 * 		1.7.1.3. init_env_path;
 * 		1.7.1.4. get_my_env_index;
 * 		1.7.1.5. ft_strdup;
 * 		1.7.1.6. ft_strjoin;
 */

void	init_env(t_all *all, char **env, char *av0)
{
	int	i;
	int	index_pwd;

	index_pwd = init_env_allocate_memory(all, env);
	i = -1;
	while (env[++i])
	{
		all->env[i] = ft_strdup(env[i]);
		init_env_err_with_exit_msh(all, all->env[i], "minishell: init_env");
	}
	if (env[index_pwd] == NULL)
	{
		all->env[i] = ft_strjoin("PWD=", all->pwd);
		init_env_err_with_exit_msh(all, all->env[i++], "minishell: init_env");
	}
	index_pwd = get_my_env_index(env, "OLDPWD", 6);
	if (env[index_pwd] == NULL)
	{
		all->env[i] = ft_strdup("OLDPWD");
		init_env_err_with_exit_msh(all, all->env[i++], "minishell: init_env");
	}
	init_env_path(all, av0, i);
}

/************************************
 * 	1.7.1.1. init_env_allocate_memory	*
 * **********************************
*/
/* Description:
 *      The function allocates memory for an all->env array.
 * Contains functions:
 * 		1.7.1.4. get_my_env_index;
 * 		1.7.1.2. init_env_err_with_exit_msh;
 */

int	init_env_allocate_memory(t_all *all, char **env)
{
	int	nb_env;
	int	index_pwd_oldpwd;
	int	nb_new_str;

	nb_env = 0;
	nb_new_str = 0;
	while (env[nb_env])
		++nb_env;
	index_pwd_oldpwd = get_my_env_index(env, "PATH", 4);
	if (!env[index_pwd_oldpwd])
		++nb_new_str;
	index_pwd_oldpwd = get_my_env_index(env, "OLDPWD", 6);
	if (!env[index_pwd_oldpwd])
		++nb_new_str;
	index_pwd_oldpwd = get_my_env_index(env, "PWD", 3);
	if (!env[index_pwd_oldpwd])
		++nb_new_str;
	all->env = (char **)malloc(sizeof(char *) * (nb_env + nb_new_str + 1));
	if (NULL == all->env)
		init_env_err_with_exit_msh(all, NULL, "minishell: init_env");
	all->env[nb_env + nb_new_str] = NULL;
	return (index_pwd_oldpwd);
}

/************************************
 * 	1.7.1.2. init_env_err_with_exit_msh	*
 * **********************************
*/
/* Description:
 *      If a malloc error occurs while creating or filling the all->env array,
 *      this function is called.
 *      This function prints an error message and exits the program minishell.
 * Contains functions:
 * 		1.7.1.2.1. completion_code_malloc_error;
 * 		1.5. exit_clean;
 */

void	init_env_err_with_exit_msh(t_all *all, char *array_null,
								   char *oper_name)
{
	completion_code_malloc_error(array_null, oper_name);
	if (NULL == array_null)
		exit_clean(all);
}

/************************************
 * 		1.7.1.3. init_env_path   		*
 * **********************************
*/
/* Description:
 *       If you use the command "unset PATH" and run the minishell in the
 *       minishell, the PATH variable will be added to the env array
 *       "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.:" and path to the
 *       minishell after char ':'.
 * Contains functions:
 * 		1.7.1.3.1. init_env_av0_path;
 * 		1.7.1.3.2. init_env_path_without_path;
 * 		1.7.1.3.3. init_env_path_with_path;
 * 		1.7.1.3. get_my_env_index;
 */

void	init_env_path(t_all *all, char *av0, int i)
{
	int		index_path;
	char	*av0_path;

	av0_path = NULL;
	init_env_av0_path(all, av0, &av0_path);
	index_path = get_my_env_index(all->env, "PATH", 4);
	if (NULL == all->env[index_path])
		init_env_path_without_path(all, av0_path, i);
	else
		init_env_path_with_path(all, av0_path, index_path);
}
