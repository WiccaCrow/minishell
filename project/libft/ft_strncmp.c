/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 09:40:54 by grvelva           #+#    #+#             */
/*   Updated: 2020/10/31 09:40:59 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	while ((n > 0) && (*ptr1 || *ptr2))
	{
		if (*ptr1 != *ptr2)
			return ((int)(*ptr1 - *ptr2));
		n--;
		ptr1++;
		ptr2++;
	}
	return (0);
}
