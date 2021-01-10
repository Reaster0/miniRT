/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/10 16:45:03 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void project(t_data *data, t_2d resolution, t_3d *triangle, int color)
{
	int i;
	int j;
	t_2d bary;

	i = 0;
	j = 0;
	while (i <= resolution.y)
	{
		while (j <= resolution.x)
		{
			x++;
		}
		i++;
	}
}

int main(void)
{
	t_vars vars;
	t_data img;

	int y = 480;
	int x = 640;
	t_3d triangle[2];
	triangle[0].x = 120.f;
	triangle[0].y = 100.f;
	triangle[0].z = 800.f;
	triangle[1].x = 420.f;
	triangle[1].y = 300.f;
	triangle[1].z = 1.f;
	triangle[3].x = 200.f;
	triangle[3].y = 200.f;
	triangle[3].z = 50.f;
	t_3d camera;
	camera.x = 0.f;
	camera.y = 0.f;
	camera.z = 0.f;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, x, y, "Hello World!");
	img = new_img(&vars, y, x);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
