/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/14 18:05:13 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3d *new_3d(float x, float y, float z)
{
	t_3d result;
	result.x = x;
	result.y = y;
	result.z = z;
	return (&result);
}

void make_ray(t_camera *vector, t_2d point)
{
	*vector->dir = multiply_v(point.x * vector->w, *vector->right);
	*vector->dir = add_product(*vector->dir, *vector->forward);
	*vector->dir = add_product(*vector->dir, multiply_v(point.y * vector->h, *vector->up));

	normalize(vector->dir);
}

t_camera pcamera(t_3d origin, t_3d target, t_3d upguide, float fov, float ratio)
{
	t_camera result;
	*result.forward = sub_product(target, origin);
	normalize(result.forward);
	*result.right = cross_product(*result.forward, upguide);
	normalize(result.right);
	*result.up = cross_product(*result.right, *result.forward);
	result.h = tan(fov);
	result.w = result.h * ratio;
	return (result);
}

void project(t_data *data, t_3d camera, t_2d resolution, t_3d *triangle, int color)
{
	t_2d count;
	t_2d bary;
	float rayt;
	float ratio;
	int fov;

	t_sphere sphere;
	sphere.startpoint = new_3d(0, 0, -55);
	sphere.r = 20;

	fov = 25 * M_PI / 180;
	ratio = resolution.x / resolution.y;
	t_2d screen_coord;
	t_camera cam;

	cam = pcamera(camera, *new_3d(0.f, 1.0f, 0.f), *new_3d(0.f, 0.f, 0.f), fov, ratio);

	while (count.x < resolution.x)
	{
		while (count.y < resolution.y)
		{
			screen_coord.x = (2.0f * count.x) / resolution.x - 1.0f;
			screen_coord.y = (-2.0f * count.y) / resolution.y + 1.0f;
			make_ray(&cam, screen_coord);
			if (inter_sphere(ray, sphere) > -1.0)
			{
				mlx_pixel_put_fast(data, count.x, count.y, color);
			}
			count.y++;
		}
		count.x++;
	}
}

int main(void)
{
	t_vars vars;
	t_data img;
	t_2d res;
	res.x = 1280;
	res.y = 720;

	t_3d triangle[3];
	triangle[0].x = 20.f;
	triangle[0].y = 10.f;
	triangle[0].z = 10.f;
	triangle[1].x = 10.f;
	triangle[1].y = 10.f;
	triangle[1].z = 20.f;
	triangle[2].x = 10.f;
	triangle[2].y = 20.f;
	triangle[2].z = 10.f;

	t_3d camera;
	camera.x = 0.f;
	camera.y = 0.f;
	camera.z = 0.f;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.x, res.y, "Hello World!");
	img = new_img(&vars, res.y, res.x);
	project(&img, camera, res, triangle, 0xFF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
