/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:42:30 by grvelva           #+#    #+#             */
/*   Updated: 2020/10/31 17:42:35 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	unsigned char	chr;

	if (c > 255)
		return (c);
	chr = (unsigned char)c;
	if (chr >= 'a' && chr <= 'z')
		return ((int)(chr + 'A' - 'a'));
	return (c);
}
