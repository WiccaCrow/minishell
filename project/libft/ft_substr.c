/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:32:26 by grvelva           #+#    #+#             */
/*   Updated: 2020/11/01 18:32:30 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	int		i;

	if (!s)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (result && start <= ft_strlen(s))
	{
		i = 0;
		while (len - i > 0)
		{
			*(result + i) = *(s + start + i);
			i++;
		}
		*(result + i) = 0;
	}
	return (result);
}
