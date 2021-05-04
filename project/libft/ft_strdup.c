/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 10:32:26 by grvelva           #+#    #+#             */
/*   Updated: 2020/11/01 18:32:30 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*result;
	int		i;

	result = (char *)malloc(ft_strlen(src) + 1);
	if (result)
	{
		i = 0;
		while (*(src + i) != 0)
		{
			*(result + i) = *(src + i);
			i++;
		}
		*(result + i) = 0;
	}
	return (result);
}
