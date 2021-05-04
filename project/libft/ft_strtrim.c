/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:32:26 by grvelva           #+#    #+#             */
/*   Updated: 2020/11/01 18:32:30 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_lencalc(char const *s1, char const *set)
{
	size_t	len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	while (ft_strchr(set, (int)*(s1 + i)) && len > 0)
	{
		i++;
		len--;
	}
	i = ft_strlen(s1) - 1;
	while (ft_strchr(set, (int)*(s1 + i)) && len > 0)
	{
		i--;
		len--;
	}
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	len = ft_lencalc(s1, set);
	result = (char *)malloc((len + 1) * sizeof(char));
	if (result)
	{
		i = 0;
		j = 0;
		while (ft_strchr(set, (int)*(s1 + j)))
			j++;
		while (i < len)
		{
			result[i] = *(s1 + j + i);
			i++;
		}
		result[i] = 0;
	}
	return (result);
}
