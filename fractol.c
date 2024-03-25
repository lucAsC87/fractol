/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucavall <lucavall@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:51:58 by lucavall          #+#    #+#             */
/*   Updated: 2024/03/23 15:06:52 by lucavall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	setup_data(t_fractal *fractal)
{
	fractal->escape_value = 4;
	fractal->iterations_definition = 100;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	fractal->zoom = 1.0;
}

static void	hooks_manager(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window, KeyPress, KeyPressMask,
		keysym_manager, fractal);
	mlx_hook(fractal->mlx_window, ButtonPress, ButtonPressMask,
		mouse_manager, fractal);
	mlx_hook(fractal->mlx_window, DestroyNotify, StructureNotifyMask,
		destroy_fractal, fractal);
}

static void	setup_fractal(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (fractal->mlx_connection == NULL)
		exit(EXIT_FAILURE);
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection,
			1000, 1000, fractal->name);
	if (fractal->mlx_window == NULL)
	{
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		exit(EXIT_FAILURE);
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection, 1000, 1000);
	if (fractal->img.img_ptr == NULL)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_connection);
		free(fractal->mlx_connection);
		exit(EXIT_FAILURE);
	}
	fractal->img.pixel_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bits_per_pixels,
			&fractal->img.line_len,
			&fractal->img.endian);
	hooks_manager(fractal);
	setup_data(fractal);
}

int	main(int argc, char *argv[])
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))
		|| (argc == 4 && !ft_strncmp(argv[1], "julia", 5)))
	{
		fractal.name = argv[1];
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			fractal.julia_x = atodbl(argv[2]);
			fractal.julia_y = atodbl(argv[3]);
		}
		setup_fractal(&fractal);
		fractal_drawer(&fractal);
		mlx_loop(fractal.mlx_connection);
	}
	else
		write(1, "Error: use ./fractol mandelbrot | julia <val1> <val2>\n", 56);
}
