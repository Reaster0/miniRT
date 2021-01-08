/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/08 21:04:54 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int point_triangle(t_2d P, t_triangle triangle)
{
	double s1 = triangle.cy - triangle.ay;
	double s2 = triangle.cx - triangle.ax;
	double s3 = triangle.by - triangle.ay;
	double s4 = P.y - triangle.ay;

	double w1 = (triangle.ax * s1 + s4 * s2 - P.x * s1) / (s3 * s2 - (triangle.bx - triangle.ax) * s1);
	double w2 = (s4 - w1 * s3) / s1;
	return (w1 >= 0 && w2 >= 0 && (w1 + w2) <= 1);
}

void create_img(t_data *img, t_triangle triangle)
{
	t_2d point;

	point.y = 0;
	while (point.y <= img->height)
	{
		point.x = 0;
		while (point.x <= img->width)
		{
			//if (point_inside_trigon(point, triangle))
			if (point_triangle(point, triangle))
			{
				mlx_pixel_put_fast(img, point.x, point.y, 0x00FF00);
			}
			point.x++;
		}
		point.y++;
	}
}

int main(void)
{
	t_vars vars;
	t_data img;
	t_triangle triangle;

	int y = 480;
	int x = 640;
	triangle.ax = 50;
	triangle.ay = 50;
	triangle.bx = 600;
	triangle.by = 120;
	triangle.cx = 25;
	triangle.cy = 300;
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, x, y, "Hello World!");
	img = new_img(&vars, y, x);
	create_img(&img, triangle);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//mlx_loop_hook(vars.mlx, next_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
