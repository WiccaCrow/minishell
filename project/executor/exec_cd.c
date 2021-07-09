#include "minishell.h"

/************************************
 * 				exec_cd				*
 * **********************************
*/
/* Description:
 * 		Change working directory.
 * 		Change env value: PWD, OLDPWD.
 * 
 * Contains functions:
 * 		change_pwd_oldpwd;
 * libft.	ft_strlen;
 * libft.	ft_strjoin;
*/

int	exec_cd(t_all *all, t_command *tmp)
{
	int		ret_chdir;
	int		i;

	g_completion_code = 0;
	i = 0;
	if (tmp->args[0] == NULL)
		return (g_completion_code = 0);
	ret_chdir = chdir(tmp->args[0]);
	if (ret_chdir == -1)
		completion_code_int_ret_error("minishell: cd: ", 1);
	else
	{
		change_oldpwd(all);
		change_pwd(all);
	}
	return (g_completion_code);
}

/************************************
 * 		 	 change_pwd				*
 * **********************************
 */
/* Description:
 * 		The function sets the new value of the 
 * 		all->pwd variable.
 * 		If the all->env array contains string with 
 * 		PWD variable, the function change this value.
 */

void	change_pwd(t_all *all)
{
	int		i;
	char	*pwd_env;

	if (all->pwd)
	{
		free(all->pwd);
		all->pwd = NULL;
	}
	all->pwd = getcwd(NULL, 0);
	i = get_my_env_index(all->env, "PWD", 3);
	if (all->env[i])
	{
		pwd_env = all->env[i];
		all->env[i] = ft_strjoin("PWD=", all->pwd);
		if (all->env[i] == NULL)
		{
			write(STDERR_FILENO, "cd: malloc error, can't change PWD in env\n",
				43);
			all->env[i] = pwd_env;
		}
		else
			free(pwd_env);
	}
}

/************************************
 * 		  change_oldpwd			*
 * **********************************
 */
/* Description:
 * 		The function finds OLDPWD strings 
 * 		in the all-> env array. Writes the value PWD to
 * 		OLDPWD before calling the cd command.
 * 		If string PWD dont't exist, set empty value OLDPWD.
 */

void	change_oldpwd(t_all *all)
{
	int		j;
	char	*oldpwd_env;
	int		i;

	i = get_my_env_index(all->env, "PWD", 3);
	j = get_my_env_index(all->env, "OLDPWD", 6);
	oldpwd_env = all->env[j];
	if (all->env[i] && all->env[j])
		all->env[j] = ft_strjoin("OLD", all->env[i]);
	else if (all->env[j])
		all->env[j] = ft_strdup("OLDPWD=");
	if (oldpwd_env && all->env[j] == NULL)
	{
		write(STDERR_FILENO, "cd: malloc error, can't change OLDPWD in env\n",
			46);
		all->env[j] = oldpwd_env;
	}
	else
		free(oldpwd_env);
}

/************************************
 * 		  get_my_env_index			*
 * **********************************
*/
/* Description:
 * 		the function finds the index of the string 
 * 		containing len_env_str bytes from the 
 * 		env_str string in the two-dimensional array 
 * 		of strings my_env.
 * 		If env_str does not contain '=', after 
 * 		comparing len_env_str bytes, the function 
 * 		checks the next character (len_env_str + 1) of 
 * 		the string in the env_my array. 
 * 		If it is '=' or the string ends, then the 
 * 		required index was found, its value is returned. 
 * 		Otherwise, the search for the row and its 
 * 		index continues.
 *
 * Return value:
 * 		Is the index of the string env_str in the 
 * 		two-dimensional array my_env, if env_str is among 
 * 		my_env. Otherwise, it returns the index of the 
 * 		NULL row in the my_env array.
 */

int	get_my_env_index(char **my_env, char *env_str, size_t len_env_str)
{
	int	i;
	int	cmp;

	i = -1;
	while (my_env[++i])
	{
		cmp = ft_strncmp(my_env[i], env_str, len_env_str);
		if (cmp == 0 && (my_env[i][len_env_str] == '='
			|| my_env[i][len_env_str] == '\0'))
			break ;
	}
	return (i);
}
