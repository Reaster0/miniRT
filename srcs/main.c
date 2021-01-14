/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/14 17:01:46 by earnaud          ###   ########.fr       */
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

t_3d getnorm2(t_3d vector)
{
	t_3d result;
	result.x = vector.x * vector.x;
	result.y = vector.y * vector.y;
	result.z = vector.z * vector.z;
	return (result);
}

float inter_sphere(t_ray ray, t_sphere sphere)
{
	float a;
	float b;
	float c;
	float discriminant;
	t_3d vector;
	vector = sub_product(*ray.startpoint, *sphere.startpoint);
	a = dot_product(*ray.startpoint, *ray.startpoint);
	b = 2.0 * dot_product(vector, *ray.dir);
	c = dot_product(vector, vector) - sphere.r * sphere.r;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		printf("je touche pas \n");
		return (-1.0);
	}
	return ((-b - sqrt(discriminant)) / (2.0 * a));
}

void make_ray(t_ray *vector, t_2d point)
{
	//vector->dir = add_product(multiply_v(point.y * vector->h, vector->up), multiply_v(vector->forward, multiply_v(vector->w, multiply_v(vector->w, add_v(point.x, vector->forward)))));

	normalize(vector->dir);
}

t_ray pcamera(t_3d origin, t_3d target, t_3d upguide, float fov, float ratio)
{
	t_ray result;
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
	t_ray ray;

	ray = pcamera(camera, *new_3d(0.f, 0.f, -1.f), *new_3d(0.f, 1.f, 0.f), fov, ratio);

	while (count.y < resolution.y)
	{
		while (count.x < resolution.x)
		{
			screen_coord.x = (2.0f * count.x) / resolution.x - 1.0f;
			screen_coord.y = (-2.0f * count.y) / resolution.y + 1.0f;
			make_ray(&ray, screen_coord);
			if (inter_sphere(ray, sphere) > -1.0)
			{
				mlx_pixel_put_fast(data, count.x, count.y, color);
			}
			count.x++;
		}
		count.y++;
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
