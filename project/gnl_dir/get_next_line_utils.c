#include "get_next_line.h"

size_t	gnl_strlen(const char *str)
{
	size_t	result;
	char	*ptr;

	result = 0;
	if (!str)
		return (0);
	ptr = (char *)str;
	while (ptr[result])
		result++;
	return (result);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*res;
	int		j;

	if (!s2)
		return (NULL);
	res = (char *)malloc((gnl_strlen(s1) + gnl_strlen(s2) + 1) * sizeof(char));
	if (res)
	{
		j = 0;
		if (s1)
			gnl_strlcpy(res, s1, gnl_strlen(s1) + 1);
		while (*(s2 + j))
		{
			res[gnl_strlen(s1) + j] = *(s2 + j);
			j++;
		}
		res[gnl_strlen(s1) + j] = 0;
	}
	if (s1)
		free(s1);
	return (res);
}

char	*buff_trim(char *buff, size_t len)
{
	char	*result;
	size_t	i;

	if (!buff)
		return (NULL);
	result = (char *)malloc((gnl_strlen(buff) - len + 1) * sizeof(char));
	if (result)
	{
		i = 0;
		while (buff[len + i] != 0)
		{
			result[i] = *(buff + len + i);
			i++;
		}
		result[i] = 0;
	}
	if (buff)
		free(buff);
	return (result);
}

void	gnl_strlcpy(char *dest, const char *src, size_t size)
{
	if (!dest || !src)
		return ;
	if (size == 0)
		return ;
	if (dest || src)
	{
		while ((size > 1) && *src != 0)
		{
			*dest++ = *src++;
			size--;
		}
		*dest = 0;
	}
}
