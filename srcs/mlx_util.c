/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:12 by earnaud           #+#    #+#             */
/*   Updated: 2021/03/21 18:17:47 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	mlx_run(t_vars *vars, t_all *all)
{
	mlx_hook(vars->win, 15, 1L << 16, refresh, all);
	mlx_hook(vars->win, 33, 1L << 17, end_of_mlx, all);
	mlx_hook(vars->win, 2, 1L << 0, key_press, all);
	mlx_loop(vars->mlx);
}

void	img_adress(t_data *data)
{
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

t_data	new_img(t_vars *vars, int y, int x)
{
	t_data img;

	img.img = mlx_new_image(vars->mlx, x, y);
	img.height = y;
	img.width = x;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	return (img);
}

char	*get_pixel(t_data *data, int x, int y)
{
	return (data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8)));
}

void	mlx_pixel_put_fast(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
