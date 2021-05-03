/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:42:30 by grvelva           #+#    #+#             */
/*   Updated: 2020/10/31 17:42:35 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n == -2147483648)
		return (12);
	if (n == 0)
		return (1);
	if (n < 0)
		return (1 + ft_intlen(-1 * n));
	while (n > 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void	ft_putbad(char *result, int n)
{
	char	*minint;
	char	*zero;
	int		i;

	minint = "-2147483648";
	zero = "0";
	if (n == 0)
	{
		result[0] = zero[0];
		result[1] = 0;
	}
	else
	{
		i = 0;
		while (i < 12)
		{
			result[i] = minint[i];
			i++;
		}
		result[i] = 0;
	}
}

static void	ft_putpoz(char *result, int n, int size)
{
	result[size] = 0;
	while (size > 0)
	{
		result[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

static void	ft_putneg(char *result, int n, int size)
{
	result[0] = '-';
	result[size] = 0;
	while (size > 1)
	{
		result[size - 1] = n % 10 + '0';
		n = n / 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		size;

	size = ft_intlen(n);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (result)
	{
		if (n == 0 || n == -2147483648)
			ft_putbad(result, n);
		else if (n > 0)
			ft_putpoz(result, n, size);
		else
			ft_putneg(result, (-1 * n), size);
	}
	return (result);
}
