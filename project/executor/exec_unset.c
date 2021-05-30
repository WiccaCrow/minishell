#include "../includes/minishell.h"

void	exec_unset_find_env_str(t_all *all, char *oper_name);
void	exec_unset_do_new_env(t_all *all, char **env_new, int nb_lines);

int	exec_unset(t_all *all)
{
	char 	**env_new;//будущий новый массив env
	int		i;
	int		j;

	j = -1;
	i = count_env_lines(all);
	i = count_lines(all, "unset", i, j);
	env_new = (char **)malloc((i + 1) * sizeof(char *));
	env_new[i] = NULL;
	exec_unset_find_env_str(all, "unset");
	exec_unset_do_new_env(all, env_new, i);
	return (0);
}

/************************************
 * 		 exec_unset_find_env_str	*
 * **********************************
 * Описание:
 * 		Функция из валидных аргументов находит строки 
 * 		среди env массива с этими аргументами. Далее 
 * 		функция освобождает память, выделенную под эти 
 * 		строки и перенаправляет указатели с найденных 
 * 		строк на NULL.
 * 
 * Функции:
 * 		check_valid_args;
 * 		find_env_str;
 */

void	exec_unset_find_env_str(t_all *all, char *oper_name)
{
	int	j;
	int	index_env_str;

	j = -1;
	while (all->args[++j])
	{
		if (!check_valid_args(all, oper_name, j, 0))// проверяет валидность введенных аргументов, 0/1 флаг - печатать/нет сообщение о валидности аргументов
			continue;
		index_env_str = find_env_str(all, oper_name, j);//нахожу индекс env строки или нулл
		if (all->env[index_env_str] != NULL)
		{
			free(all->env[index_env_str]);
			all->env[index_env_str] = NULL;
		}
	}
}

/************************************
 * 	  exec_unset_delete_env_str		*
 * **********************************
 * Описание:
 * 		Функция заменяет старый массив 
 * 		env на новый массив env (без 
 * 		удаленных строк).
 */

void	exec_unset_do_new_env(t_all *all, char **env_new, int nb_lines)
{
	int	j;
	int	i;

	j = -1;
	i = 0;
	while (++j < nb_lines)
	{
		while (all->env[j + i] == NULL)
			++i;
		env_new[j] = all->env[j + i];
	}
	free(all->env);
	all->env = env_new;
}

// export A AA= AAA AAAA=1234 AAAAA="12345" AAAAAA='123456'