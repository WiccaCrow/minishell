/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 09:40:54 by grvelva           #+#    #+#             */
/*   Updated: 2020/10/30 09:40:59 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	result;

	if (!dest || !src)
		return (0);
	result = 0;
	while (*(src + result) != 0)
		result++;
	if (result == 0)
	{
		*dest = 0;
		return (result);
	}
	if (size == 0)
		return (result);
	if (dest || src)
	{
		while ((size > 1) && *src != 0)
		{
			*dest++ = *src++;
			size--;
		}
		*dest = 0;
	}
	return (result);
}
