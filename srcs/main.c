/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/01/29 17:00:48 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
//faire une structure qui englobe toutes les autres

t_light *new_light(t_3d point, int intens)
{
	t_light *light;
	light = malloc(sizeof(t_light *));
	light->point = point;
	light->intens = intens;
}

int intersections(t_ray *ray, t_plane **plane, t_sphere **sphere, t_triangle **triangle, t_square **square, t_cylinder **cylinder)
{
	int ret;
	t_light *light;
	ret = 0;
	light = new_light(new_3d(-5.f, 5, -10), 100000);

	if (inter_spheres(ray, sphere))
		ret = 1;
	if (inter_planes(ray, plane))
		ret = 1;
	if (inter_triangles(ray, triangle))
		ret = 1;
	if (inter_squares(ray, square))
		ret = 1;
	if (inter_cylinders(ray, cylinder))
		ret = 1;
	//faire le calcul de lumiere ici

	if (ret == 1)
	{
		light->hit = calculate(*ray, ray->t);
		light->normale = sub_product(light->hit.startpoint, ray->shape_point);
		normalize(&light->normale);
		//faire une fonction qui fait ça pour toutes les couleurs
		int r = get_r(ray->color) * light->intens * dot_product(get_norm(sub_product(light->point, light->hit.endpoint)), light->normale) / length2(sub_product(light->point, light->hit.endpoint));
	}
	return (ret);
}

void project(t_data *data, t_2d resolution, int color)
{
	t_2d count;
	float ratio;
	float fov;

	t_sphere **sphere;
	sphere = malloc(sizeof(t_sphere *) * 3);
	sphere[0] = new_sphere(new_3d(0.0f, 0.0f, 7.0f), 4.0f, 0x00FF00);
	sphere[1] = new_sphere(new_3d(-15.f, 3.f, 10.f), 4.f, 0xFF0000);
	sphere[2] = NULL;
	t_plane **plane;
	plane = malloc(sizeof(t_plane *) * 3);
	plane[0] = new_plane(new_3d(0.f, -4.f, 0.f), new_3d(0.f, 1.f, 0.f), 0x0000FF);
	plane[1] = new_plane(new_3d(0.f, -0.5f, 21.f), new_3d(0.f, 0.0f, -1.f), 0x4d1aec);
	plane[2] = NULL;
	t_triangle **triangle;
	triangle = malloc(sizeof(t_triangle *) * 1);
	triangle[0] = new_triangle(new_3d(-10, 20, 20), new_3d(10, 20, 20), new_3d(0, 40, 20), 0xFFFF00);
	triangle[1] = NULL;
	t_square **square;
	square = malloc(sizeof(t_square) * 2);
	square[0] = new_square(new_3d(35, 0, 19), new_3d(5, 0, 10), new_3d(5, 20, 10), new_3d(35, 20, 10), 0x00FFFF);
	square[1] = NULL;
	t_cylinder **cylinder;
	cylinder = malloc(sizeof(t_cylinder *) * 2);
	cylinder[0] = new_cylinder(new_3d(-7.5f, -2.f, 10.f), new_3d(0.f, 1.f, 0.f), new_2d(4, 2), create_trgb(0, 237, 153, 83));
	cylinder[1] = NULL;

	fov = 60.f * M_PI / 180.f;
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
			if (intersections(&ray, plane, sphere, triangle, square, cylinder))
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

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.x, res.y, "MiniRT");
	img = new_img(&vars, res.y, res.x);

	project(&img, res, 0xFF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
