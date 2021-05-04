/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 09:40:54 by grvelva           #+#    #+#             */
/*   Updated: 2020/10/30 09:40:59 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*hsk;

	hsk = (char *)haystack;
	while (*hsk && len >= ft_strlen(needle))
	{
		if (ft_strncmp(hsk, needle, ft_strlen(needle)) == 0)
			return (hsk);
		hsk++;
		len--;
	}
	if (*needle == 0)
		return (hsk);
	return (NULL);
}
