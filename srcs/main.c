/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/12 18:35:02 by earnaud          ###   ########.fr       */
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

float inter_sphere(t_ray ray, t_ray sphere)
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

void project(t_data *data, t_3d camera, t_2d resolution, t_3d *triangle, int color)
{
	int i;
	int j;
	t_2d bary;
	float rayt;
	float ratio;
	int fov;

	t_ray sphere;
	sphere.startpoint = new_3d(0, 0, -55);
	sphere.r = 20;

	fov = 53 * M_PI / 180;
	ratio = resolution.x / resolution.y;
	i = 0;
	j = 0;
	t_3d r;
	t_ray ray;
	ray.startpoint = &camera;
	ray.dir = &r;

	while (i < resolution.y)
	{
		while (j < resolution.x)
		{
			r = *new_3d(j - resolution.x / 2, i - resolution.y / 2, -resolution.x / (2 * tan(fov / 2)));
			normalize(&r);
			if (inter_sphere(ray, sphere) > -1.0)
			{
				mlx_pixel_put_fast(data, j, i, color);
				printf("a l'emplacement j= %d et i =%d y a un pixel", j, i);
			}
			printf("\n %d", inter_sphere(ray, sphere));
			j++;
		}
		i++;
	}
	printf("i =%d, j =%d\n", i, j);
}

int main(void)
{
	t_vars vars;
	t_data img;
	t_2d res;
	res.y = 1024;
	res.x = 1024;

	t_3d triangle[2];
	triangle[0].x = 20.f;
	triangle[0].y = 10.f;
	triangle[0].z = 10.f;
	triangle[1].x = 10.f;
	triangle[1].y = 10.f;
	triangle[1].z = 20.f;
	triangle[3].x = 10.f;
	triangle[3].y = 20.f;
	triangle[3].z = 10.f;

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
