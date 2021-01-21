/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/21 17:53:01 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int intersections(t_ray *ray, t_plane **plane, t_sphere **sphere)
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

	t_sphere **sphere;
	sphere = malloc(sizeof(t_plane) * 3);
	sphere[0] = new_sphere(new_3d(0.0f, 0.0f, 20.0f), 5.0f, 0x00FF00);
	sphere[1] = new_sphere(new_3d(7.f, 0.f, 18.f), 5.f, 0xFF0000);

	t_plane **plane;
	plane = malloc(sizeof(t_plane) * 3);
	plane[0] = new_plane(new_3d(0.f, -4.f, 0.f), new_3d(0.f, 1.f, 0.f), 0x0000FF);
	plane[1] = new_plane(new_3d(0.f, -0.5f, 0.f), new_3d(2.f, 1.0f, 0.f), 0xFFFFFF);

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
			if (intersections(&ray, plane, sphere))
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
