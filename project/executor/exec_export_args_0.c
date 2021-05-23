#include "../includes/minishell.h"

void	print_export(char **sort_env_index);

int	exec_export(t_all *all)
{
	int	i;

	i = 0;
	while (all->env[i])
		++i;
write(1, "test  1\n", 9);
	if (!all->args[0])
		sort_env(all, i, -1, 0);
	else
		subjoin_env(all, i, -1);
write(1, "test  2\n", 9);
	return (0);
}

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

int	ft_strcmp_s1_less_s2(char *str1, char *str2)
{
	while (*str1 == *str2 && *str2 && *str1)
	{
		++str1;
		++str2;
	}
	if (*str1 < *str2)
		return (1);
	return (0);
}

int	do_sort_index(char ***sort_env_index, int **sort, int i)
{
	int	k;

	k = -1;
	*sort_env_index = (char **)malloc((i + 1) * sizeof(char *));
	(*sort_env_index)[i] = NULL;
	*sort = (int *)malloc((i + 1) * sizeof(int));//индексы возрастания строк
	(*sort)[i] = 0;
	while (++k < i)
		(*sort)[k] = 1;
	if (*sort_env_index == NULL || *sort == NULL)
	{
		write(STDOUT_FILENO, "Error: malloc error. Try again.\n", 33);
		return (1);
	}
	return (0);
}

void	sort_env(t_all *all, int i, int k, int j)
{
	int		j_zero;
	char	**sort_env_index;
	int		*sort;

	if (do_sort_index(&sort_env_index, &sort, i))
		return ;
	j_zero = 0;
	while (i)
	{
		k = -1;
		j = 0;
		while (!sort[j_zero] && all->env[j_zero])
			++j_zero;
		j += j_zero;
		while (all->env[++k])
			if (ft_strcmp_s1_less_s2(all->env[j], all->env[k]) && sort[k])
				j = k;
		sort_env_index[--i] = all->env[j];
		sort[j] = 0;
	}
	print_export(sort_env_index);
	free_sort_index(sort_env_index, sort);
}

void	print_export(char **sort_env_index)
{
	int		i;
	char	*len_equal;

	i = -1;
	while (sort_env_index[++i])
	{
		write(STDOUT_FILENO, "declare -x ", ft_strlen("declare -x "));
		len_equal = ft_strchr(sort_env_index[i], '=');
		if (len_equal++)
		{
			write(STDOUT_FILENO, sort_env_index[i], len_equal - sort_env_index[i]);
			write(STDOUT_FILENO, "\"", 1);
			write(STDOUT_FILENO, len_equal, ft_strlen(len_equal));
			write(STDOUT_FILENO, "\"\n", 2);
		}
		else
		{
			write(STDOUT_FILENO, sort_env_index[i], ft_strlen(sort_env_index[i]));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
}

// export A AA= AAA AAAA=1234 AAAAA="12345" AAAAAA='123456'
// export B BA= BAA BAAA=1234 BAAAA="12345" BAAAAA='123456'
// export A=1 AA=12345 AAA= AAAA AAAAA="12" AAAAAA='56'
