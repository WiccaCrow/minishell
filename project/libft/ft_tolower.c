/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:42:30 by grvelva           #+#    #+#             */
/*   Updated: 2020/12/11 16:34:23 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int c)
{
	unsigned char	chr;

	if (c > 255)
		return (c);
	chr = (unsigned char)c;
	if (chr >= 'A' && chr <= 'Z')
		return ((int)(chr - 'A' + 'a'));
	return (c);
}
