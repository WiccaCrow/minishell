/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grvelva <grvelva@student.21-school>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:42:30 by grvelva           #+#    #+#             */
/*   Updated: 2020/11/01 17:42:35 by grvelva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	unsigned char	chr;

	if (c > 255)
		return (0);
	chr = (unsigned char)c;
	if (((chr >= 65) && (chr <= 90)) || ((chr >= 97) && (chr <= 122)))
		return (1);
	if (chr >= '0' && chr <= '9')
		return (1);
	return (0);
}
