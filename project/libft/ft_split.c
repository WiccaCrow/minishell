/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdulcie 				                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 00:59:23 by mdulcie           #+#    #+#             */
/*   Updated: 2020/11/13 01:13:54 by mdulcie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static void	ft_free(char **s, int dostr)
{
	if (*s == NULL)
		while (dostr--)
			free(*(--s));
	free(s);
}

static char	*ft_strdup_c(const char *s1, int count)
{
	char	*c_copy;

	c_copy = malloc((count + 1) * sizeof(char));
	if (!c_copy)
		return (NULL);
	c_copy[count] = 0;
	while (count--)
		c_copy[count] = s1[count];
	return (c_copy);
}

static int	ft_str(char const *s, char c)
{
	int	i;
	int	str;

	i = 0;
	str = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			str++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (str);
}

char	**ft_do_split(char const *s, char c, int i, char **massstr)
{
	int	count;
	int	dostr;
	int	str;

	str = ft_str(s, c);
	dostr = 0;
	while (s[i] && massstr)
	{
		count = 0;
		while (s[i] && s[i] != c && count++ <= i)
			++i;
		++dostr;
		*massstr = ft_strdup_c(&s[i - count], count);
		if (!(*massstr))
			ft_free(massstr, dostr);
		if (--str)
			massstr++;
		while (s[i] && s[i] == c)
			++i;
	}
	return (massstr - (dostr - 1));
}

char	**ft_split(char const *s, char c)
{
	char	**massstr;
	int		str;
	int		i;

	if (!s)
		return (NULL);
	massstr = NULL;
	i = 0;
	while (s[i] && s[i] == c)
		++i;
	str = ft_str(s, c);
	massstr = (char **)malloc((str + 1) * sizeof(char *));
	if (!massstr)
		return (NULL);
	massstr[str] = NULL;
	if (s[i])
		ft_do_split(s, c, i, massstr);
	return (massstr);
}
