/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/19 17:16:07 by earnaud          ###   ########.fr       */
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
{ //le rayon part toujours en 0.0.1
	t_ray result;
	result.startpoint = camera.startpoint;

	result.endpoint = camera.forward;
	result.endpoint.x = point.x * camera.h * camera.right.x;
	result.endpoint.y = point.y * camera.w * camera.up.y;
	printf("le resultat de l'operation x=%f\n", point.y * camera.w * camera.up.y);
	//printf("endpoint\nx=%f\ny=%f\nz=%f\n", result.endpoint.x, result.endpoint.y, result.endpoint.z);
	normalize(&result.endpoint);
	result.t = 1.0e30f;

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
	printf("forward = %f\n%f\n%f\nup =%f\n%f\n%f\n", result.forward.x, result.forward.y, result.forward.z, result.up.x, result.up.y, result.up.z);
	return (result);
}

void project(t_data *data, t_3d camera, t_2d resolution, t_3d *triangle, int color)
{
	t_2d count;
	count.x = 0;
	float ratio;
	int fov;
	t_2d bary;

	t_sphere sphere;
	sphere.startpoint = new_3d(0.0f, 0.0f, 2.0f);
	sphere.r = 1.0f;

	t_plane plane;
	plane.position = new_3d(0.f, 0.f, 0.f);
	plane.normal = new_3d(0.f, 1.f, 0.f);

	fov = 25.f * M_PI / 180.f;
	ratio = resolution.x / resolution.y;
	t_2d screen_coord;
	t_camera cam;
	cam = new_camera(new_3d(0.f, 0.f, 0.f), new_3d(0.f, 0.f, 1.f), new_3d(0.f, 1.f, 0.f), fov, ratio);
	t_ray ray;

	count.x = 1.0f;
	count.y = 1.0f;
	while (count.x < resolution.x)
	{
		count.y = 0;
		while (count.y < resolution.y)
		{
			screen_coord.x = (2.0f * count.x) / resolution.x - 1.0f;
			screen_coord.y = (-2.0f * count.y) / resolution.y + 1.0f;
			//printf("screen x=%f\nscreen y=%f\n", screen_coord.x, screen_coord.y);
			ray = make_ray(cam, screen_coord);
			if (inter_sphere(&ray, sphere))
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
	res.x = 1020.f;
	res.y = 720.f;

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
	camera.x = -5.0f;
	camera.y = 1.0f;
	camera.z = 0.0f;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.x, res.y, "Hello World!");
	img = new_img(&vars, res.y, res.x);

	project(&img, camera, res, triangle, 0xFF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
