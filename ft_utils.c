/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucavall <lucavall@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:49:27 by lucavall          #+#    #+#             */
/*   Updated: 2024/03/22 18:42:42 by lucavall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(double unscaled_num, double new_min, double new_max, double old_max)
{
	return ((new_max - new_min) * unscaled_num / old_max + new_min);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && n > 1)
	{
		s1++;
		s2++;
		n--;
	}
	return (((unsigned char)(*s1) - (unsigned char)(*s2)));
}

t_complex	complex_add(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.x = z1.x + z2.x;
	result.y = z1.y + z2.y;
	return (result);
}

t_complex	complex_squared(t_complex z)
{
	t_complex	result;

	result.x = (z.x * z.x) - (z.y * z.y);
	result.y = 2 * z.x * z.y;
	return (result);
}

double	atodbl(char *str)
{
	long	integer_part;
	double	fractional_part;
	double	pow;
	int		sign;

	integer_part = 0;
	fractional_part = 0;
	pow = 1;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32 || *str == 43 || *str == 45)
	{
		if (*str == 45)
			sign = -sign;
		++str;
	}
	while (*str != 46 && *str)
		integer_part = (integer_part * 10) + (*str++ - 48);
	if (*str == 46)
		++str;
	while (*str)
	{
		pow /= 10;
		fractional_part = fractional_part + (*str++ - 48) * pow;
	}
	return ((integer_part + fractional_part) * sign);
}
