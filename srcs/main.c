/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earnaud <earnaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:25:08 by earnaud           #+#    #+#             */
/*   Updated: 2021/02/03 21:55:19 by earnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
//faire une structure qui englobe toutes les autres

t_light *new_light(t_3d point, int intens)
{
	t_light *light;
	light = malloc(sizeof(t_light));
	light->point = point;
	light->intens = intens;
	return (light);
}

int intens_color(t_ray *ray, t_light *light, int color, int min_color)
{
	float temp;
	int result;

	temp = ((float)color / 255) * (light->intens * dot_product(get_norm(sub_product(light->point, light->hit.shape_point)), light->hit.shape_normale) / length2(sub_product(light->point, light->hit.endpoint)));

	//un soucis sur la correction gamma
	//temp /= pow(1.f, 2.2);

	result = temp * 255;

	if (result > 255)
		result = 255;
	if (result < min_color)
		result = min_color;
	return (result);
}

int inter_light(t_ray *ray, t_light *light, t_shapes *shapes, int min_color)
{
	light->hit = calculate(*ray, ray->t);
	light->normale = ray->shape_normale;

	t_ray l_ray;
	l_ray.startpoint = add_product(multiply_v(0.001, light->normale), light->hit.endpoint);
	l_ray.endpoint = get_norm(sub_product(light->point, light->hit.endpoint));
	l_ray.t = 1.0e30f;
	l_ray.color = 0xFFFFFF;

	int r = intens_color(ray, light, get_r(ray->color), get_r(min_color));
	int g = intens_color(ray, light, get_g(ray->color), get_g(min_color));
	int b = intens_color(ray, light, get_b(ray->color), get_b(min_color));

	ray->color = create_trgb(get_t(ray->color), r, g, b);

	intersections(&l_ray, shapes, 0);
	if (sqr(l_ray.t) < length2(sub_product(light->point, light->hit.endpoint)))
		ray->color = min_color;
	//ray->color = min_color;
}

int intersections(t_ray *ray, t_shapes *shapes, int inter_l)
{
	int ret;
	t_light **light;

	light = malloc(sizeof(t_light *) * 3);
	light[0] = new_light(new_3d(9.f, 5, -3), 120);
	light[1] = new_light(new_3d(-12.f, 5.f, -4.f), 20);
	light[1] = NULL;
	ret = 0;

	if (inter_spheres(ray, shapes->sphere))
		ret = 1;
	if (inter_planes(ray, shapes->plane))
		ret = 1;
	// if (inter_triangles(ray, triangle))
	// 	ret = 1;
	// if (inter_squares(ray, square))
	// 	ret = 1;
	// if (inter_cylinders(ray, cylinder))
	// 	ret = 1;
	//faire le calcul de lumiere ici

	if (ret == 1 && inter_l)
		inter_lights(ray, light, shapes);

	return (ret);
}

void project(t_data *data, t_2d resolution, int color)
{
	t_2d count;
	float ratio;
	float fov;
	t_shapes shapes;

	shapes.sphere = malloc(sizeof(t_sphere *) * 6);
	shapes.sphere[0] = new_sphere(new_3d(1.0f, 0.0f, 14.0f), 4.f, 0x900C3F);
	//shapes.sphere[1] = new_sphere(new_3d(-60.f, 3.f, 20.f), 45.f, 0xFF0000);
	shapes.sphere[1] = new_sphere(new_3d(7.f, 1.f, 10.f), 4.f, 0x59e1a7);
	shapes.sphere[2] = new_sphere(new_3d(-20.f, -1.5f, 13.f), 4.f, 0xFF00FF);
	shapes.sphere[3] = new_sphere(new_3d(-5.f, 2.f, 7.f), 3.f, 0x00FFFF);
	shapes.sphere[4] = NULL;

	shapes.plane = malloc(sizeof(t_plane *) * 6);
	shapes.plane[1] = new_plane(new_3d(0.f, -4.f, 0.f), new_3d(0.f, 1.f, 0.f), 0x0000FF);
	shapes.plane[0] = new_plane(new_3d(0.f, -0.5f, 34.f), new_3d(0.f, 0.0f, -1.f), create_trgb(0, 140, 80, 180));
	shapes.plane[2] = new_plane(new_3d(0.f, 20.f, 0.f), new_3d(0.f, -1.f, 0.f), 0xFF5733);
	shapes.plane[3] = new_plane(new_3d(30.f, 0.f, 0.f), new_3d(-1.f, 0.f, 0.f), 0xFF0000);
	shapes.plane[4] = new_plane(new_3d(-30.f, 0.f, 0.f), new_3d(1.f, 0.f, 0.f), 0xFF0000);
	shapes.plane[5] = NULL;

	shapes.triangle = malloc(sizeof(t_triangle *) * 1);
	shapes.triangle[0] = new_triangle(new_3d(-10, 20, 20), new_3d(10, 20, 20), new_3d(0, 40, 20), 0xFFFF00);
	shapes.triangle[1] = NULL;

	shapes.square = malloc(sizeof(t_square) * 2);
	shapes.square[0] = new_square(new_3d(35, 0, 19), new_3d(5, 0, 10), new_3d(5, 20, 10), new_3d(35, 20, 10), 0x00FFFF);
	shapes.square[1] = NULL;

	shapes.cylinder = malloc(sizeof(t_cylinder *) * 2);
	shapes.cylinder[0] = new_cylinder(new_3d(-7.5f, -2.f, 10.f), new_3d(0.f, 1.f, 0.f), new_2d(4, 2), create_trgb(0, 237, 153, 83));
	shapes.cylinder[1] = NULL;

	fov = 50.f * M_PI / 180.f;
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
			if (intersections(&ray, &shapes, 1))
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
	res.x = 1200.f;
	res.y = 720.f;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, res.x, res.y, "MiniRT");
	img = new_img(&vars, res.y, res.x);

	project(&img, res, 0xFF0000);
	ft_putstr_fd("finished\n", 1);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
