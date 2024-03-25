/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucavall <lucavall@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 14:51:02 by lucavall          #+#    #+#             */
/*   Updated: 2024/03/23 16:59:25 by lucavall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	alt_pixel_put(int x, int y, t_img *image, int color)
{
	int	offset;

	offset = (y * image->line_len) + (x * (image->bits_per_pixels / 8));
	*(unsigned int *)(image->pixel_ptr + offset) = color;
}

static void	set_fractal_type(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	pixel_manager(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.x = (map(x, -2, 2, 1000) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, 2, -2, 1000) * fractal->zoom) + fractal->shift_y;
	set_fractal_type(&z, &c, fractal);
	while (i < fractal->iterations_definition)
	{
		z = complex_add(complex_squared(z), c);
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			color = map(i, 0x000000, 0xFFFFFF, fractal->iterations_definition);
			alt_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		++i;
	}
	alt_pixel_put(x, y, &fractal->img, 0xFF00FF);
}

void	fractal_drawer(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < 1000)
	{
		x = -1;
		while (++x < 1000)
			pixel_manager(x, y, fractal);
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
}
