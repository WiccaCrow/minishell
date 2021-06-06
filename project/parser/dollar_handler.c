#include "../includes/minishell.h"

/**
 * Функция получает ключ в командной строке
*/

char *get_key(int i, char *line)
{
	char *key;
	
	key = ft_strdup(&line[i + 1]);
	if (key)
	{
		i = 0;
		if (key[0] == '?')
		{
			key[1] = 0;
			return (key);
		}
		while (key[i] && key[i] != ' ' && key[i] != '"' && key[i] != '$')
			i++;
		key[i] = 0;
	}
	return (key);
}

/**
 * Функция получает значение переменной из env по ее ключу
*/

char *get_value(const char *key, t_all *all)
{
	int	i;
	int	j;
	char *value;

	printf("%s\n", key);
	if (key && *key == '?')
	{
		return (ft_itoa(all->completion_code));
	}
	i = 0;
	while (key && all->env[i])
	{
		j = 0;
		while (all->env[i][j] == key[j])
			j++;
		if (!key[j] && all->env[i][j] == '=')
		{
			value = ft_strdup(&all->env[i][j + 1]);
			return (value);
		}
		i++;
	}
	return (strdup(""));
}

/**
 * Функция заменяет переменную в строке на ее значение
*/

int	get_arg_from_env(int i, t_all *all)
{
	char	*key;
	char	*value;
	char	*result;
	size_t	size;
	int 	j;
	int 	k;
	
	key = get_key(i, all->line);
	value = get_value(key, all);
	size = ft_strlen(all->line) - ft_strlen(key) + ft_strlen(value);
	result = (char *)ft_calloc(size, sizeof (char));
	if (result)
	{
		j = 0;
		while (j < i)
		{
			result[j] = all->line[j];
			j++;
		}
		k = j + (int)ft_strlen(key) + 1;
		while (value[j - i])
		{
			result[j] = value[j - i];
			j++;
		}
		while (all->line[k])
		{
			result[j++] = all->line[k++];
		}
		free(all->line);
		all->line = result;
		return (0);
	}
	return (1);
}

/**
 * Функция обрабатывает неэкранированные символы '$' в строке
 * 
 * При нахождении такого символа переменная заменяется ее значением, и проход
 * по строке начинается заново
*/

int	dollar_handler(t_all *all)
{
	int		i;
	int 	flag;
	
	i = 0;
	flag = 0;
	while (all->line[i] && all->line[i] != ';')
	{
		if (all->line[i] == '\\' && !(flag & QUOTE))
		{
			flag = flag | SHIELD;
			i++;
		}
		else if (all->line[i] == '\'' && !(flag & SHIELD))
		{
			flag = flag ^ QUOTE;
			i++;
		}
		if (all->line[i] == '$' && !flag)
		{
			get_arg_from_env(i, all);
			i = 0;
		}
		else
			i++;
		if ((flag & SHIELD) && all->line[i])
			flag = flag & ~(SHIELD);
	}
	return(1);
	
}