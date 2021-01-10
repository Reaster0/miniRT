/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/10 18:39:03 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void project(t_data *data, t_3d camera, t_3d vect, t_2d resolution, t_3d *triangle, int color)
{
	int i;
	int j;
	t_2d bary;
	float rayt;

	i = 0;
	j = 0;
	//changer le fov en changeant les coordonees x et y du vecteur
	//fov etant la distance de la fenetre qui inclinera le vecteur
	t_3d window;
	window.z = 53;
	window.x = (resolution.x / 2) + camera.x;
	window.y = (resolution.y / 2) + camera.y;

	while (i <= resolution.y)
	{
		while (j <= resolution.x)
		{
			window.x = (j / 2) + camera.x;
			window.y = (i / 2) + camera.y;
			vect = sub_product(camera, window);
			if (moller_trumbore(camera, vect, triangle, &rayt, &bary.x, &bary.y))
				mlx_pixel_put_fast(data, j, i, color);
			j++;
		}
		i++;
	}
}

int main(void)
{
	t_vars vars;
	t_data img;
	t_2d res;
	res.y = 480;
	res.x = 640;
	t_3d triangle[2];
	triangle[0].x = 120.f;
	triangle[0].y = 0.f;
	triangle[0].z = 800.f;
	triangle[1].x = 420.f;
	triangle[1].y = 300.f;
	triangle[1].z = 1.f;
	triangle[3].x = 200.f;
	triangle[3].y = 0.f;
	triangle[3].z = 50.f;
	t_3d camera;
	camera.x = 0.f;
	camera.y = 0.f;
	camera.z = 0.f;
	t_3d dir;
	dir.x = 0.f;
	dir.y = 0.f;
	dir.z = 1.f;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.x, res.y, "Hello World!");
	img = new_img(&vars, res.y, res.x);
	project(&img, camera, dir, res, triangle, 0xFF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
