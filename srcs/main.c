/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/20 17:21:58 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3d new_3d(float x, float y, float z)
{
	t_3d result;
	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

t_ray make_ray(t_camera camera, t_2d point)
{
	t_ray result;
	result.startpoint = camera.startpoint;
	result.endpoint = camera.forward;
	result.endpoint = add_product(result.endpoint, multiply_v(point.x * camera.w, camera.right));
	result.endpoint = add_product(result.endpoint, multiply_v(point.y * camera.h, camera.up));
	normalize(&result.endpoint);
	result.t = 1.0e30f;
	result.color = 0x00FFFFFF;

	return (result);
}

t_camera new_camera(t_3d origin, t_3d target, t_3d upguide, float fov, float ratio)
{ //pensez a fix le cas ou upguide == target
	t_camera result;
	result.startpoint = origin;
	result.forward = sub_product(target, origin);
	normalize(&result.forward);
	result.right = cross_product(result.forward, upguide);
	normalize(&result.right);
	result.up = cross_product(result.right, result.forward);

	result.h = tan(fov);
	result.w = result.h * ratio;
	//printf("forward = %f\n%f\n%f\nup =%f\n%f\n%f\n", result.forward.x, result.forward.y, result.forward.z, result.up.x, result.up.y, result.up.z);
	return (result);
}

int inter_spheres(t_ray *ray, t_sphere *sphere)
{
	int i = 0;
	int ret;
	ret = 0;
	//autant de spheres
	while (i < 2)
	{
		if (inter_sphere(ray, sphere[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

int inter_planes(t_ray *ray, t_plane *plane)
{
	int i = 0;
	int ret;
	ret = 0;
	//autant de planes
	while (i > 2)
	{
		if (inter_plane(ray, plane[i]))
			ret = 1;
		i++;
	}
	return (ret);
}

int intersections(t_ray *ray, t_plane *plane, t_sphere *sphere)
{
	int ret;
	ret = 0;
	if (inter_spheres(ray, sphere))
		ret = 1;
	if (inter_planes(ray, plane))
		ret = 1;
	return (ret);
}

void project(t_data *data, t_3d camera, t_2d resolution, int color)
{
	t_2d count;
	float ratio;
	float fov;

	t_sphere sphere[2];
	sphere[0].startpoint = new_3d(0.0f, 0.0f, 20.0f);
	sphere[0].r = 5.0f;
	sphere[0].color = 0x00FF00;

	sphere[1].color = 0xFF0000;
	sphere[1].r = 5.f;
	sphere[1].startpoint = new_3d(7.f, 0.f, 18.f);

	t_plane plane[2];
	plane[0].position = new_3d(0.f, -0.5f, 0.f);
	plane[0].normal = new_3d(0.f, 1.f, 0.f);
	plane[0].color = 0x0000FF;

	plane[1]

		fov = 25.f * M_PI / 180.f;
	ratio = resolution.x / resolution.y;
	t_2d screen_coord;
	t_camera cam;
	cam = new_camera(new_3d(0.f, 0.f, 0.f), new_3d(0.0f, 0.0f, 1.f), new_3d(0.f, 1.f, 0.f), fov, ratio);
	t_ray ray;

	count.x = 0;
	while (count.x < resolution.x)
	{
		count.y = 0;
		while (count.y < resolution.y)
		{
			screen_coord.x = (2.0f * count.x) / resolution.x - 1.0f;
			screen_coord.y = (-2.0f * count.y) / resolution.y + 1.0f;
			ray = make_ray(cam, screen_coord);
			if (inter_sphere2(&ray, sphere) || inter_plane(&ray, plane))
			{
				mlx_pixel_put_fast(data, count.x, count.y, ray.color);
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
	res.x = 1020.f;
	res.y = 720.f;

	t_3d camera;
	camera.x = -5.0f;
	camera.y = 1.0f;
	camera.z = 0.0f;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.x, res.y, "Hello World!");
	img = new_img(&vars, res.y, res.x);

	project(&img, camera, res, 0xFF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
