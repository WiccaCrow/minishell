/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:32:26 by grvelva           #+#    #+#             */
/*   Updated: 2020/11/01 18:32:30 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (result)
	{
		i = 0;
		while (*(s1 + i))
		{
			result[i] = *(s1 + i);
			i++;
		}
		j = 0;
		while (*(s2 + j))
		{
			result[i + j] = *(s2 + j);
			j++;
		}
		result[i + j] = 0;
	}
	return (result);
}
