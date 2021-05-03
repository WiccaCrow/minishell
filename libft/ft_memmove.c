/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 09:40:54 by grvelva           #+#    #+#             */
/*   Updated: 2020/10/29 09:40:59 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_dest;

	tmp_dest = (unsigned char *)dest;
	if (dest || src)
	{
		if (dest < src)
		{
			while (n > 0)
			{
				*tmp_dest++ = *(unsigned char *)src++;
				n--;
			}
		}
		else
		{
			while (n > 0)
			{
				*(tmp_dest + n - 1) = *(unsigned char *)(src + n - 1);
				n--;
			}
		}
	}
	return (dest);
}
