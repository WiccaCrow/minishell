#include "../includes/minishell.h"

void	test_print_pwd(t_all *all, char *str_pwd);
int	change_pwd_oldpwd(t_all *all);
int	get_my_env_index(char **my_env, char *env_str, size_t len_env_str);

int	exec_cd(t_all *all)
{
	int		ret_chdir;
	int		i;

// test_print_pwd(all);
	ret_chdir = 0;
	i = 0;
	if (all->args[0] == NULL)
		return (0);
	ret_chdir = chdir(all->args[0]);

	if (ret_chdir == -1)
	{
		write(STDERR_FILENO, "minishell: cd: ", 16);
		char *err = strerror(errno);
		write(STDERR_FILENO, err, ft_strlen(err));
		write(STDERR_FILENO, "\n", 1);
	}
	else
	{
// если pwd нет в env, необходимо его создать
			i = change_pwd_oldpwd(all);
			all->pwd = getcwd(NULL, 0);
			if (i >= 0)
				all->env[i] = ft_strjoin("PWD=", all->pwd);
	}
// test_print_pwd(all, "PWD=");///////////////////////
// test_print_pwd(all, "OLDPWD=");///////////////////////
	return (ret_chdir);
}

void	test_print_pwd(t_all *all, char *str_pwd)
{
	int i;

	i = get_my_env_index(all->env, str_pwd, ft_strlen(str_pwd));
	if (all->env[i])
	{
		write(1, all->env[i], ft_strlen(all->env[i]));
		write(1, "\n", 1);
	}
	else
		write(1, "not pwd/oldpwd\n", 16);
}

/************************************
 * 		  change_pwd_oldpwd			*
 * **********************************
 * Описание:
 * 		функция находит в массиве all->env строки 
 * 		PWD и OLDPWD. В строку OLDPWD записывает 
 * 		полное имя рабочего каталога до вызова 
 * 		команды cd. Память из-под строки PWD 
 * 		освобождает и зануляет.
 *
 * Возвращаемое значение:
 * 		int. Если в массиве all->env строка PWD 
 * 		была найдена, возвращает индекс
 * 		строки PWD в массиве all->env.
 *		В противном случае возвращает -1.
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
 * Описание:
 * 		функция находит индекс строки, содержащей 
 * 		len_env_str байт от строки env_str,
 * 		в двумерном массиве строк my_env.
 * 		Если env_str не содержит '=', после сравнения
 * 		len_env_str байт, функция проверяет следующий 
 * 		символ (len_env_str + 1) строки в массиве 
 * 		env_my. Если это '=' или строка закончилась, 
 * 		значит искомый индекс найден, возвращается его 
 * 		значение. В противном случае поиск строки и ее 
 * 		индекса продолжается.
 *
 * Возвращаемое значение:
 * 		int индекс строки env_str в двумерном 
 * 		массиве строк my_env, если env_str есть 
 * 		среди my_env. В противном случае 
 * 		возвращает индекс строки NULL в массиве my_env.
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
