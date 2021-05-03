/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:42:30 by grvelva           #+#    #+#             */
/*   Updated: 2020/10/31 17:42:35 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_is_num(char c)
{
	return ((c >= '0') && (c <= '9'));
}

int	ft_atoi(char *str)
{
	int			sign;
	long long	r;

	sign = 1;
	r = 0;
	while (((*str >= 9) && (*str <= 13)) || (*str == 32))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (ft_is_num(*str) && (r >= -2147483648) && (r < 2147483648))
	{
		r = r * 10 + (*str - '0');
		str++;
	}
	r = r * sign;
	if (r < -2147483648)
		r = 0;
	if (r > 2147483647)
		r = -1;
	return (r);
}
