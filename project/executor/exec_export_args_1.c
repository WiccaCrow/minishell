#include "../includes/minishell.h"

void	change_env_str(t_all *all, int j, int index);
int	count_lines(t_all *all, char *oper_name, int nb_env_lines, int j);
int	check_double_args(char **args);

void	subjoin_env(t_all *all, int i, int j)//subjoin_env(all, i, -1);
{
	char 	**env_new;//будущий новый массив env
	int		index;//индекс искомой строки в массиве env

	i = count_lines(all, "export", i, j);
	env_new = (char **)malloc((i + 1) * sizeof(char *));
	env_new[i] = NULL;
	while (all->args[++j])
	{
		if (!check_valid_args(all, "export", j, 0))// проверяет валидность введенных аргументов, 0/1 флаг - печатать/нет сообщение о валидности аргументов
			continue;
		if (check_double_args(&(all->args[j])))//проверяет наличие этого же аргумента среди последующих аргументов 1 - повторяется, 0 - нет повторов
			continue;
if (j == 1)
printf("test test 1\n");


		index = find_env_str(all, "export", j);//нахожу индекс env строки или нулл
		if (all->env[index] == NULL)
		{
if (j == 1)
printf("test test 2\n");
			env_new[--i] = ft_strdup(all->args[j]);//если такой переменной не было, создать ее
printf("env_new i = %s || i = %d\n", env_new[i], i);
		}
		else
		{
			if (ft_strchr(all->args[j], '=') != NULL)
				change_env_str(all, j, index);//перезаписывает существующую env переменную
		}
	}
	while (--i >= 0)
	{
		env_new[i] = all->env[i];
printf("env_new i = %s || i = %d\n", env_new[i], i);
	}
	free(all->env);
	all->env = env_new;
}

int	count_lines(t_all *all, char *oper_name, int nb_env_lines, int j)
{
	int		index;
	
	while (all->args[++j])// пока не переберу все аргументы
	{
		if (!check_valid_args(all, oper_name, j, 1))// проверяет валидность введенных аргументов
			continue;
		if (check_double_args(&(all->args[j])))//проверяет наличие этого же аргумента среди последующих аргументов 1 - повторяется, 0 - нет повторов
			continue;
		index = find_env_str(all, oper_name, j);//нахожу индекс env строки или нулл
		if (!ft_strncmp(oper_name, "export", ft_strlen(oper_name)))
		{
			if (all->env[index] == NULL)//если нет искомой строки (не было такой переменной), добавляю будущее количество строк в новом массиве env
				++nb_env_lines;
		}
		else
		{
			write(1, "command unset.\n", 16);
			if (all->env[index])
				--nb_env_lines;
		}
	}
	return (nb_env_lines);
}

int	check_double_args(char **args)
{
	int	i;
	int	nb_args;

	i = 0;
	while (args[0][i] != '=' && args[0][i])
		++i;
	nb_args = 0;
	while (args[++nb_args])// перебираю все последующие аргументы
	{
		if (!ft_strncmp(args[0], args[nb_args], i))
		{
			printf("args0 = %s\nargsj = %s\ni = %d\n\n", args[0], args[nb_args], i);
			if (args[nb_args][i] == '=' || args[nb_args][i] == '\0')//если встречу совпадение, возвращаю 1
			{
				// printf("i = %d || args0 %s || argsj %s\n", i, args[0], args[j]);
				return (1);
			}
		}
	}
	return (0);
}

int	find_env_str(t_all *all, char *oper_name, int j)
{
	size_t	len_env_str;
	int		index;

	if (!ft_strncmp(oper_name, "unset", 5))
		len_env_str = ft_strlen(all->args[j]);//длина сравниваемой части строки равна длине аргумента
	else if (!ft_strncmp(oper_name, "export", 6) && ft_strchr(all->args[j], '=') == NULL)//если команда unset или в аргументе отсутствует символ '=')
	{
		len_env_str = ft_strlen(all->args[j]);//длина сравниваемой части строки равна длине аргумента
		write(1, all->args[j], len_env_str);
		write(1, "\n", 1);
		printf("len_env_str = %zu\n", len_env_str);

	}
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

int	check_valid_args(t_all *all, char *oper_name, int j, int flag_print)//oper_name имя операции для проверки валидности аргументов
{
	int		i;

	i = 0;
	while (all->args[j][i] != '\0')
	{
		if (all->args[j][i] == '=' && !ft_strncmp(oper_name, "export", 6))
			break;
		if (!(all->args[j][i] == '=' && !ft_strncmp(oper_name, "unset", 6)) &&
			((all->args[j][i] >= 'a' && all->args[j][i] <= 'z') ||
			(all->args[j][i] >= 'A' && all->args[j][i] <= 'Z') ||
			(all->args[j][i] >= '0' && all->args[j][i] <= '9' && i != 0) ||
			all->args[j][i] == '_'))
				++i;
		else
			return (print_not_valid(all->args[j], oper_name, flag_print));
	}
	return (1);
}

int	print_not_valid(char *args_name, char *operation_name, int flag_print)//args_name имя невалидного аргумента, operation_name имя операции для печати, flag_print печатать/не печатать
{
	if (flag_print)
	{
		write(STDOUT_FILENO, "minishell: ", 12);
		write(STDOUT_FILENO, operation_name, ft_strlen(operation_name));
		write(STDOUT_FILENO, ": `", 4);
		write(STDOUT_FILENO, args_name, ft_strlen(args_name));
		write(STDOUT_FILENO, "': not a valid identifier\n", 27);
	}
	return (0);
}

// export A 2AA= A-AA A.AAA=1234 AA~AAA="12345" AAAAAA='123456'
// export B 2BA= B-AA B.AAA=1234 BA~AAA="12345" BAAAAA='123456'
// export 12 AA aA A=qwer 1A=1 AAA.=2
// export QWERTY1 QWERTY2= 1QWERTY3= 2QWERTY4