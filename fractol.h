/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucavall <lucavall@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:36:43 by lucavall          #+#    #+#             */
/*   Updated: 2024/03/23 15:03:26 by lucavall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <unistd.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"

typedef struct s_complex
{
	double	x;
	double	y;
}			t_complex;

typedef struct s_img
{
	void	*img_ptr;
	char	*pixel_ptr;
	int		bits_per_pixels;
	int		endian;
	int		line_len;
}			t_img;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	double	escape_value;
	int		iterations_definition;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}			t_fractal;

double		map(double unscaled_num, double new_min,
				double new_max, double old_max);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
t_complex	complex_add(t_complex z1, t_complex z2);
t_complex	complex_squared(t_complex z);
double		atodbl(char *str);
int			destroy_fractal(t_fractal *fractal);
int			keysym_manager(int keysym, t_fractal *fractal);
int			mouse_manager(int button, int x, int y, t_fractal *fractal);
void		fractal_drawer(t_fractal *fractal);

#endif
