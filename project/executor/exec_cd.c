#include "../includes/minishell.h"

/************************************
 * 				exec_cd				*
 * **********************************
 * Description:
 * 		Change working directory.
 * 		Change env value: PWD, OLDPWD.
 * 
 * Contains functions:
 * 		change_pwd_oldpwd;
 * libft.	ft_strlen;
 * libft.	ft_strjoin;
*/

int	exec_cd(t_all *all)
{
	int		ret_chdir;
	int		i;

	all->completion_code = 0;
	i = 0;
	if (all->args[0] == NULL)
		return (all->completion_code = 0);
	ret_chdir = chdir(all->args[0]);
	if (ret_chdir == -1)
	{
		write(STDERR_FILENO, "minishell: cd: ", 16);
		char *err = strerror(errno);
		write(STDERR_FILENO, err, ft_strlen(err));
		write(STDERR_FILENO, "\n", 1);
		all->completion_code = 1;
	}
	else
	{
		i = change_pwd_oldpwd(all);
		all->pwd = getcwd(NULL, 0);
		if (i >= 0)
			all->env[i] = ft_strjoin("PWD=", all->pwd);
	}
	return (all->completion_code);
}

/************************************
 * 		  change_pwd_oldpwd			*
 * **********************************
 * Description:
 * 		The function finds PWD and OLDPWD strings 
 * 		in the all-> env array. Writes the full 
 * 		name of the working directory to the string 
 * 		OLDPWD before calling the cd command. Memory 
 * 		from under the PWD line frees and zeroes out.
 *
 * Return value:
 * 		int. If the PWD string was found in the 
 * 		all-> env array, returns the index of the PWD 
 * 		string in the all-> env array.
 * 		Otherwise, returns -1.
 */

int	change_pwd_oldpwd(t_all *all)
{
	int	i;
	int	j;

	i = get_my_env_index(all->env, "PWD=", 4);
	j = get_my_env_index(all->env, "OLDPWD=", 7);
	all->oldpwd = all->pwd;
	if (all->env[j])
	{
		free(all->env[j]);
		all->env[j] = NULL;
		all->env[j] = ft_strjoin("OLDPWD=", all->pwd);
	}
	if (all->pwd)
	{
		free(all->pwd);
		all->pwd = NULL;
	}
	if (all->env[i])
	{
		free(all->env[i]);
		all->env[i] = NULL;
		return (i);
	}
	return (-1);
}

/************************************
 * 		  get_my_env_index			*
 * **********************************
 * Description:
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

	i = 0;
	cmp = ft_strncmp(my_env[i], env_str, len_env_str);
	while (my_env[i] && cmp)
	{
		++i;
		if (my_env[i])
		{
			cmp = ft_strncmp(my_env[i], env_str, len_env_str);
			if (!cmp && ft_strchr(env_str, '=') == NULL)
			{
				if (my_env[i][len_env_str + 1] == '=' || my_env[i][len_env_str + 1] == '\0')
				return (i);
			}
		}
	}
	return (i);
}
