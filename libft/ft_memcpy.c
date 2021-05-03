/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 09:40:54 by grvelva           #+#    #+#             */
/*   Updated: 2020/10/28 09:40:59 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*tmp_dest;

	tmp_dest = (unsigned char *)dest;
	if (dest || src)
	{
		while (n > 0)
		{
			*tmp_dest = *(unsigned char *)src;
			src++;
			tmp_dest++;
			n--;
		}
	}
	return (dest);
}
