#include "minishell.h"

/**
 * Функция получает ключ в командной строке
*/

char	*get_key(int i, char *line)
{
	char	*key;

	key = ft_strdup(&line[i + 1]);
	if (key)
	{
		i = 0;
		if (key[0] == '?')
		{
			key[1] = 0;
			return (key);
		}
		while (key[i] && !ft_strchr(" \"\'$",key[i]))
			i++;
		key[i] = 0;
	}
	return (key);
}

/**
 * Функция получает значение переменной из env по ее ключу
*/

char	*get_value(const char *key, t_all *all)
{
	int		i;
	int		j;
	char	*value;

	if (key && *key == '?')
		return (ft_itoa(g_completion_code));
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

static int	replace_key(char **line, char *key, const char *value, int i)
{
	char	*result;
	size_t	size;
	int		j;
	int		k;

	size = ft_strlen((*line)) - ft_strlen(key) + ft_strlen(value);
	result = (char *)ft_calloc(size, sizeof (char));
	if (result)
	{
		j = -1;
		while (++j < i)
			result[j] = (*line)[j];
		k = j + (int)ft_strlen(key) + 1;
		j--;
		while (value[++j - i])
			result[j] = value[j - i];
		while ((*line)[k])
			result[j++] = (*line)[k++];
		free((*line));
		(*line) = result;
		return (0);
	}
	return (1);
}

int	get_arg_from_env(int i, t_all *all)
{
	char	*key;
	char	*value;
	int 	ret;

	key = get_key(i, all->line);
	value = get_value(key, all);
	ret = replace_key(&all->line, key, value, i);
	ft_free((void *)&key);
	ft_free((void *)&value);
	return (ret);
}

/**
 * Функция обрабатывает неэкранированные символы '$' в строке
 * 
 * При нахождении такого символа переменная заменяется ее значением, и проход
 * по строке начинается заново
*/

int	dollar_handler(t_all *all)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (all->line[i] && all->line[i] != ';')
	{
		if (all->line[i] == '\\' && !(flag & QUOTE) && !(flag & SHIELD))
			flag = flag | SHIELD;
		else if (all->line[i] == '\"' && !(flag & SHIELD) && !(flag & QUOTE))
			flag = flag ^ DOUBLE_QUOTE;
		else if (all->line[i] == '\'' && !(flag & SHIELD) && !(flag & DOUBLE_QUOTE))
			flag = flag ^ QUOTE;
		else if (all->line[i] == '$' && !(flag & SHIELD) && !(flag & QUOTE))
		{
			get_arg_from_env(i, all);
			i = -1;
		}
		else
			if ((flag & SHIELD) && all->line[i])
				flag = flag & ~(SHIELD);
		i++;
	}
	return (1);
}
