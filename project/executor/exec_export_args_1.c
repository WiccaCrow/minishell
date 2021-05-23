#include "../includes/minishell.h"

int		find_env_str(t_all *all, int j);
void	change_env_str(t_all *all, int j, int index);
int		check_valid_args(t_all *all, int j, int flag_print);

void	subjoin_env(t_all *all, int i, int j)
{
	char 	**env_new;//будущий новый массив env
	int		index;//индекс искомой строки в массиве env 

	while (all->args[++j])// пока не переберу все аргументы
	{
		if (!check_valid_args(all, j, 0))// проверяет валидность введенных аргументов
			continue;
		index = find_env_str(all, j);//нахожу индекс env строки или нулл
		if (all->env[index] == NULL)//если нет искомой строки (не было такой переменной), добавляю будущее количество строк в новом массиве env
			++i;
	}
	env_new = (char **)malloc((i + 1) * sizeof(char *));
	env_new[i] = NULL;
	while (--j >= 0)
	{
		if (!check_valid_args(all, j, 1))// проверяет валидность введенных аргументов, 0/1 флаг - печатать/нет сообщение о валидности аргументов
			continue;
		index = find_env_str(all, j);//нахожу индекс env строки или нулл
		if (all->env[index] == NULL)
			env_new[--i] = ft_strdup(all->args[j]);//если такой переменной не было, создать ее
		else
		{
			if (ft_strchr(all->args[j], '=') != NULL)
				change_env_str(all, j, index);//перезаписывает существующую env переменную
		}
	}
	while (--i >= 0)
		env_new[i] = all->env[i];
	free(all->env);
	all->env = env_new;
}

int	find_env_str(t_all *all, int j)
{
	size_t	len_env_str;
	int		index;

	if (ft_strchr(all->args[j], '=') == NULL)//если в аргументе отсутствует символ '='
		len_env_str = ft_strlen(all->args[j]) + 1;//длина сравниваемой части строки равна длине аргумента
	else
		len_env_str = ft_strchr(all->args[j], '=') - all->args[j];//длина сравн.части равна длине аргумента до '='
	index = get_my_env_index(all->env, all->args[j], len_env_str);// определила индекс искомой строки при ее наличии в массиве
	return (index);
}

void	change_env_str(t_all *all, int j, int index)
{
	int	len_args;

	len_args = ft_strlen(all->args[j]);
	free(all->env[index]);
	all->env[index] = NULL;
	all->env[index] = ft_strdup(all->args[j]);
}

int	check_valid_args(t_all *all, int j, int flag_print)
{
	int		i;
	char	*sign_equal;

	i = 0;
	sign_equal = ft_strchr(all->args[j], '=');
	if (sign_equal == NULL)
	{
		while (all->args[j][i])
			++i;
		sign_equal = &all->args[j][i];
	}
	i = 0;
	while (all->args[j][i] != '\0' && &(all->args[j][i]) != sign_equal)
	{
		if ((all->args[j][i] >= 65 && all->args[j][i] <= 90) ||
			(all->args[j][i] >= 97 && all->args[j][i] <= 122) ||
			all->args[j][i] == 95)
			++i;
		else if (all->args[j][i] >= 48 && all->args[j][i] <= 57)// первый символ переменной может быть буква или '_'
		{
			if (i != 0)
				++i;
			else
			{
				if (flag_print)
				{
					write(STDOUT_FILENO, "minishell: export: `", 21);
					write(STDOUT_FILENO, all->args[j], ft_strlen(all->args[j]));
					write(STDOUT_FILENO, "': not a valid identifier\n", 27);
				}
				return (0);
			}
		}
		else
		{
			if (flag_print)
			{
				write(STDOUT_FILENO, "minishell: export: `", 21);
				write(STDOUT_FILENO, all->args[j], ft_strlen(all->args[j]));
				write(STDOUT_FILENO, "': not a valid identifier\n", 27);
			}
			return (0);
		}
	}
	return (1);
}


// export A 2AA= A-AA A.AAA=1234 AA~AAA="12345" AAAAAA='123456'
// export B 2BA= B-AA B.AAA=1234 BA~AAA="12345" BAAAAA='123456'
// export 12 AA aA A=qwer 1A=1 AAA.=2